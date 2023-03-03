#include "errors.h"

QString ErrorsTranslator::translateLoginError(LoginErrorType error) {
    switch (error) {
    case LoginErrorType::IllegalState:
        return tr("Something went wrong. Please fill a bug report in "
                  "https://github.com/SfietKonstantin/harbour-elephant-seal/issues.");
    case LoginErrorType::Url:
        return tr("Invalid Mastodon URL");
    case LoginErrorType::Http:
        return tr("Failed to connect to Mastodon instance");
    default:
        return tr("Unknown error");
    }
}
