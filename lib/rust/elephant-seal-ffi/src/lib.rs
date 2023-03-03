use cxx_qt_lib::QString;
use elephant_seal_rs::errors::LoginError;
use elephant_seal_rs::Mastodon;
use log::error;
use std::path::PathBuf;
use std::pin::Pin;
use std::sync::Arc;
use tokio::runtime::Runtime;
use tokio::sync::Mutex;

#[cxx::bridge]
pub mod cxxbridge {
    enum LoginErrorType {
        IllegalState,
        Url,
        Http,
    }

    unsafe extern "C++" {
        include!("lib/errors.h");
        include!("glue/glue.h");
        include!("cxx-qt-lib/qstring.h");
        type QString = cxx_qt_lib::QString;
        type EventBus;
        type LoginErrorType;

        fn event_bus_send_pre_login_success(bus: Pin<&'static mut EventBus>, url: &QString);
        fn event_bus_send_login_success(bus: Pin<&'static mut EventBus>);
        fn event_bus_send_pre_login_error(
            bus: Pin<&'static mut EventBus>,
            error: LoginErrorType,
            detailed_error: &QString,
        );
        fn event_bus_send_login_error(
            bus: Pin<&'static mut EventBus>,
            error: LoginErrorType,
            detailed_error: &QString,
        );
    }

    extern "Rust" {
        type RustMastodon;

        fn rust_mastodon_init();
        fn rust_mastodon_new(config_path: &QString) -> Box<RustMastodon>;
        fn rust_mastodon_is_logged_in(rust_mastodon: &RustMastodon) -> bool;
        fn rust_mastodon_prepare_login(
            rust_mastodon: &RustMastodon,
            server_url: &QString,
            bus: Pin<&'static mut EventBus>,
        );
        fn rust_mastodon_login(
            rust_mastodon: &RustMastodon,
            code: &QString,
            bus: Pin<&'static mut EventBus>,
        );
    }
}

unsafe impl Send for cxxbridge::EventBus {}

unsafe impl Sync for cxxbridge::EventBus {}

struct RustMastodon {
    mastodon: Arc<Mutex<Mastodon>>,
    runtime: Runtime,
}

impl RustMastodon {
    fn new(config_path: &QString) -> Self {
        let config_path = PathBuf::from(config_path.to_string());

        RustMastodon {
            mastodon: Arc::new(Mutex::new(Mastodon::new(config_path))),
            runtime: Runtime::new().unwrap(),
        }
    }
}

fn rust_mastodon_init() {
    elephant_seal_rs::init()
}

fn rust_mastodon_new(config_path: &QString) -> Box<RustMastodon> {
    Box::new(RustMastodon::new(config_path))
}

fn rust_mastodon_is_logged_in(rust_mastodon: &RustMastodon) -> bool {
    let mastodon = rust_mastodon.mastodon.clone();
    rust_mastodon.runtime.block_on(async move {
        let mastodon = mastodon.lock().await;
        mastodon.is_logged_in()
    })
}

fn handle_login_error<F>(
    err: LoginError,
    bus: Pin<&'static mut cxxbridge::EventBus>,
    f: F,
    log: &str,
) where
    F: FnOnce(Pin<&'static mut cxxbridge::EventBus>, cxxbridge::LoginErrorType, &QString),
{
    error!("{} {:?}", log, err);

    let error = match err {
        LoginError::IllegalState(_) | LoginError::Save(_) => {
            cxxbridge::LoginErrorType::IllegalState
        }
        LoginError::Url(_) => cxxbridge::LoginErrorType::Url,
        LoginError::Http(_) => cxxbridge::LoginErrorType::Http,
    };
    let detailed_error = format!("{:?}", err);
    let detailed_error = QString::from(&detailed_error);
    f(bus, error, &detailed_error);
}

fn rust_mastodon_prepare_login(
    rust_mastodon: &RustMastodon,
    server: &QString,
    bus: Pin<&'static mut cxxbridge::EventBus>,
) {
    let mastodon = rust_mastodon.mastodon.clone();
    let server = server.to_string();
    rust_mastodon.runtime.spawn(async move {
        let mut mastodon = mastodon.lock().await;
        let result = mastodon.prepare_login(server).await;
        match result {
            Ok(url) => {
                let url = QString::from(&url);
                cxxbridge::event_bus_send_pre_login_success(bus, &url);
            }
            Err(err) => handle_login_error(
                err,
                bus,
                cxxbridge::event_bus_send_pre_login_error,
                "Could not prepare login.",
            ),
        }
    });
}

fn rust_mastodon_login(
    rust_mastodon: &RustMastodon,
    code: &QString,
    bus: Pin<&'static mut cxxbridge::EventBus>,
) {
    let mastodon = rust_mastodon.mastodon.clone();
    let code = code.to_string();
    rust_mastodon.runtime.spawn(async move {
        let mut mastodon = mastodon.lock().await;
        let result = mastodon.login(code).await;
        match result {
            Ok(()) => cxxbridge::event_bus_send_login_success(bus),
            Err(err) => handle_login_error(
                err,
                bus,
                cxxbridge::event_bus_send_login_error,
                "Could not login.",
            ),
        }
    });
}
