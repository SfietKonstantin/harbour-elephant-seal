use crate::errors::LoginError;
use crate::settings::SettingsManager;
use crate::{Application, ClientContext, Mastodon, MastodonClient, Settings};
use crabodon::rest::{ApplicationBody, MastodonAuthApi, TokenBody};
use pretend::{Pretend, Url};
use pretend_reqwest::Client as RClient;

const REDIRECT_URI: &str = "urn:ietf:wg:oauth:2.0:oob";

impl Mastodon {
    pub async fn prepare_login(&mut self, server: String) -> Result<String, LoginError> {
        let server_url = Url::parse(&server)?;
        let client = Pretend::for_client(RClient::default()).with_url(server_url.clone());

        let application = Self::get_application_from_client(&client).await?;
        let login_url = format!(
            "{}/oauth/authorize?response_type=code&client_id={}&redirect_uri={}",
            server, application.client_id, REDIRECT_URI
        );

        self.client_ctx = Some(ClientContext {
            client,
            server: server_url,
            application,
        });

        Ok(login_url)
    }

    async fn get_application_from_client(
        client: &MastodonClient,
    ) -> Result<Application, LoginError> {
        let application =
            ApplicationBody::for_client("Elephant seal".to_string(), REDIRECT_URI.to_string());
        let application = client.post_application(application).await?;
        let application = application.value();
        let application = Application {
            vapid_key: application.vapid_key,
            client_id: application.client_id,
            client_secret: application.client_secret,
        };
        Ok(application)
    }

    pub async fn login(&mut self, code: String) -> Result<(), LoginError> {
        if let Some(client_ctx) = self.client_ctx.as_ref() {
            let client_id = client_ctx.application.client_id.clone();
            let client_secret = client_ctx.application.client_secret.clone();
            let token =
                TokenBody::with_code(code, client_id, client_secret, REDIRECT_URI.to_string());
            let token = client_ctx.client.post_token(token).await?;
            let token = token.value();

            let auth_info = Settings {
                server: client_ctx.server.clone(),
                application: client_ctx.application.clone(),
                token: token.access_token,
            };
            SettingsManager::new(&self.config_path).save_settings(&auth_info)?;
            self.token = Some(auth_info.token);
            Ok(())
        } else {
            Err(LoginError::IllegalState(
                "prepare_login should be called first".to_string(),
            ))
        }
    }
}
