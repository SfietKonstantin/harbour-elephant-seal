#include <lib/mastodon.h>

#include <elephant-seal-ffi/src/lib.rs.h>

#include <QStandardPaths>

namespace {

using namespace rust::cxxqtlib1;

class RustGlueMastodonPrivate : public MastodonHook {
public:
    explicit RustGlueMastodonPrivate()
        : m_rustMastodon(rust_mastodon_new(getConfigPath())) //
    {
    }

    bool isLoggedIn() const override {
        return rust_mastodon_is_logged_in(*m_rustMastodon);
    }

    void preLogin(const QString &serverUrl, EventBus &bus) override {
        rust_mastodon_prepare_login(*m_rustMastodon, serverUrl, bus);
    }

    void login(const QString &code, EventBus &bus) override {
        rust_mastodon_login(*m_rustMastodon, code, bus);
    }

    static QString getConfigPath() {
        return QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);
    }

private:
    rust::Box<RustMastodon> m_rustMastodon;
};

} // namespace

void event_bus_send_pre_login_success(EventBus &bus, const QString &url) {
    EventBus::sendPreLoginSuccess(bus, url);
}

void event_bus_send_login_success(EventBus &bus) {
    EventBus::sendLoginSuccess(bus);
}

void event_bus_send_pre_login_error(EventBus &bus, LoginErrorType error, const QString &detailedError) {
    EventBus::sendPreLoginError(bus, error, detailedError);
}

void event_bus_send_login_error(EventBus &bus, LoginErrorType error, const QString &detailedError) {
    EventBus::sendLoginError(bus, error, detailedError);
}

std::unique_ptr<MastodonHook> Mastodon::makeHook() {
    return std::make_unique<RustGlueMastodonPrivate>();
}
