use crate::settings::SettingsManager;
use crate::Mastodon;
use std::path::PathBuf;

impl Mastodon {
    pub fn new(config_path: PathBuf) -> Self {
        let mut instance = Mastodon {
            config_path,
            client_ctx: None,
            token: None,
        };
        instance.init();
        instance
    }

    fn init(&mut self) {
        if let Some(settings) = SettingsManager::new(&self.config_path).load_settings() {
            self.init_client(settings.server, settings.application);
        }
    }
}
