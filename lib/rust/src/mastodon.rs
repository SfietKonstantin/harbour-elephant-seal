mod login;

use cxx_qt_lib::QString;
use pretend::interceptor::NoopRequestInterceptor;
use pretend::resolver::UrlResolver;
use pretend::Pretend;
use pretend_reqwest::Client as RClient;

type MastodonClient = Pretend<RClient, UrlResolver, NoopRequestInterceptor>;

pub struct Mastodon {
    client_ctx: Option<ClientContext>,
}

struct ClientContext {
    client: MastodonClient,
}

impl Mastodon {
    pub fn new() -> Self {
        Mastodon { client_ctx: None }
    }

    pub fn init() {
        // Force linking against cxx_qt_lib
        QString::default();
    }
}
