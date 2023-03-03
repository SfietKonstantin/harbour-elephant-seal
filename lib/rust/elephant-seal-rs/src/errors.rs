use std::io;
use thiserror::Error;

#[derive(Debug, Error)]
pub enum SettingsLoadError {
    #[error("Failed to open settings file")]
    Io(#[from] io::Error),
    #[error("Failed to read settings")]
    Deserialize(#[from] serde_yaml::Error),
}

#[derive(Debug, Error)]
pub enum SettingsSaveError {
    #[error("Failed to save settings file")]
    Io(#[from] io::Error),
    #[error("Failed to format settings")]
    Serialize(#[from] serde_yaml::Error),
}

#[derive(Debug, Error)]
pub enum LoginError {
    #[error("Invalid state: {0}")]
    IllegalState(String),
    #[error("Failed to save authentication info")]
    Save(#[from] SettingsSaveError),
    #[error("URL parse error")]
    Url(#[from] pretend::url::ParseError),
    #[error("HTTP error")]
    Http(#[from] pretend::Error),
}
