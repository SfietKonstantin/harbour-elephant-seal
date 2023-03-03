pub mod errors;

mod init;
mod login;
mod settings;

use pretend::interceptor::NoopRequestInterceptor;
use pretend::resolver::UrlResolver;
use pretend::{Pretend, Url};
use pretend_reqwest::Client as RClient;
use serde::{Deserialize, Serialize};
use std::path::PathBuf;

type MastodonClient = Pretend<RClient, UrlResolver, NoopRequestInterceptor>;

#[derive(Clone, Serialize, Deserialize)]
struct Application {
    vapid_key: String,
    client_id: String,
    client_secret: String,
}

#[derive(Clone, Serialize, Deserialize)]
struct Settings {
    server: Url,
    application: Application,
    token: String,
}

pub struct Mastodon {
    config_path: PathBuf,
    client_ctx: Option<ClientContext>,
    token: Option<String>,
}

impl Mastodon {
    pub fn is_logged_in(&self) -> bool {
        self.client_ctx.is_some()
    }

    fn init_client(&mut self, server: Url, application: Application) -> &ClientContext {
        let client = Pretend::for_client(RClient::default()).with_url(server.clone());
        self.client_ctx.get_or_insert(ClientContext {
            client,
            server,
            application,
        })
    }
}

struct ClientContext {
    client: MastodonClient,
    server: Url,
    application: Application,
}

pub fn init() {
    env_logger::init()
}
