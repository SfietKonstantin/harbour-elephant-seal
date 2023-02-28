use super::{ClientContext, Mastodon};
use anyhow::Result;
use crabodon::rest::{ApplicationBody, MastodonAuthApi};
use pretend::{Pretend, Url};
use pretend_reqwest::Client as RClient;

const REDIRECT_URI: &str = "urn:ietf:wg:oauth:2.0:oob";

impl Mastodon {
    pub async fn prepare_login(&mut self, server: String) -> Result<String> {
        let server_url = Url::parse(&server)?;
        let client = Pretend::for_client(RClient::default()).with_url(server_url);

        let application =
            ApplicationBody::for_client("Elephant seal".to_string(), REDIRECT_URI.to_string());
        let application = client.post_application(application).await?;
        let application = application.value();

        self.client_ctx = Some(ClientContext { client });

        let login_url = format!(
            "{}/oauth/authorize?response_type=code&client_id={}&redirect_uri={}",
            server, application.client_id, REDIRECT_URI
        );
        Ok(login_url)
    }
}
