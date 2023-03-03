use crate::errors::{SettingsLoadError, SettingsSaveError};
use crate::Settings;
use log::error;
use std::fs::File;
use std::io::{BufReader, BufWriter};
use std::path::{Path, PathBuf};

pub(crate) struct SettingsManager<'a> {
    config_path: &'a Path,
}

impl<'a> SettingsManager<'a> {
    pub(crate) fn new(config_path: &'a Path) -> Self {
        SettingsManager { config_path }
    }

    pub(crate) fn load_settings(&self) -> Option<Settings> {
        match self.handle_load_auth_info() {
            Ok(auth_info) => Some(auth_info),
            Err(err) => {
                error!(
                    "Failed to load auth info from {}: {:?}",
                    self.auth_info_path().display(),
                    err
                );
                None
            }
        }
    }
    pub(crate) fn save_settings(&self, auth_info: &Settings) -> Result<(), SettingsSaveError> {
        let path = self.auth_info_path();
        let file = File::create(path)?;
        let writer = BufWriter::new(file);
        serde_yaml::to_writer(writer, auth_info)?;
        Ok(())
    }

    fn handle_load_auth_info(&self) -> Result<Settings, SettingsLoadError> {
        let path = self.auth_info_path();
        let file = File::open(path)?;
        let reader = BufReader::new(file);
        let auth_info = serde_yaml::from_reader(reader)?;
        Ok(auth_info)
    }

    fn auth_info_path(&self) -> PathBuf {
        self.config_path.join("auth-info.yaml")
    }
}
