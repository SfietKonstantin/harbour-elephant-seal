#include <lib/mastodon.h>

#include <QTimer>

namespace {

class ShimMastodonPrivate : public MastodonHook {
public:
    bool isLoggedIn() const override {
        return !qgetenv("TEST_LOGGED_IN").isEmpty();
    }

    void preLogin(const QString &serverUrl, EventBus &bus) override {
        handleLogin(serverUrl, bus, &ShimMastodonPrivate::sendLoginComplete, &EventBus::sendPreLoginError);
    }

    void login(const QString &code, EventBus &bus) override {
        handleLogin(code, bus, &EventBus::sendLoginSuccess, &EventBus::sendLoginError);
    }

private:
    template <class S, class E>
    static void handleLogin(const QString &input, EventBus &bus, S successCallback, E errorCallback) {
        QTimer::singleShot(1000, &bus, [&bus, input, successCallback, errorCallback] {
            if (input == "error-illegal") {
                errorCallback(bus, LoginErrorType::IllegalState, "illegal state");
            } else if (input == "error-url") {
                errorCallback(bus, LoginErrorType::Url, "url error");
            } else if (input == "error-http") {
                errorCallback(bus, LoginErrorType::Http, "http error");
            } else {
                successCallback(bus);
            }
        });
    }

    static void sendLoginComplete(EventBus &bus) {
        EventBus::sendPreLoginSuccess(bus, "");
    }
};

} // namespace

std::unique_ptr<MastodonHook> Mastodon::makeHook() {
    return std::make_unique<ShimMastodonPrivate>();
}
