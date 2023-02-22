use crate::Mastodon;
use log::error;
use std::pin::Pin;
use std::sync::Arc;
use tokio::runtime::Runtime;
use tokio::sync::Mutex;

#[cxx::bridge]
pub mod cxxbridge {

    struct FeedStatus {
        account: String,
        content: String,
    }

    unsafe extern "C++" {
        include!("glue/glue.h");
        type EventBus;

        fn event_bus_send_display_code_input(bus: Pin<&'static mut EventBus>);
    }

    extern "Rust" {
        type RustMastodon;

        fn rust_mastodon_new() -> Box<RustMastodon>;
        fn rust_mastodon_prepare_login(
            rust_mastodon: &RustMastodon,
            server_url: &str,
            bus: Pin<&'static mut EventBus>,
        );
    }
}

unsafe impl Send for cxxbridge::EventBus {}

unsafe impl Sync for cxxbridge::EventBus {}

struct RustMastodon {
    runtime: Runtime,
    mastodon: Arc<Mutex<Mastodon>>,
}

impl RustMastodon {
    fn new() -> Self {
        RustMastodon {
            runtime: Runtime::new().unwrap(),
            mastodon: Arc::new(Mutex::new(Mastodon::new())),
        }
    }
}

fn rust_mastodon_new() -> Box<RustMastodon> {
    Box::new(RustMastodon::new())
}
fn rust_mastodon_prepare_login(
    rust_mastodon: &RustMastodon,
    server: &str,
    bus: Pin<&'static mut cxxbridge::EventBus>,
) {
    let mastodon = rust_mastodon.mastodon.clone();
    let server = server.to_string();
    rust_mastodon.runtime.spawn(async move {
        let mut mastodon = mastodon.lock().await;
        let result = mastodon.prepare_login(server).await;
        match result {
            Ok(()) => cxxbridge::event_bus_send_display_code_input(bus),
            Err(err) => {
                error!("Could not prepare login. {:?}", err);
            }
        }
    });
}
