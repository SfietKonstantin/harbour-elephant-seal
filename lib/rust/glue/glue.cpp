#include <lib/mastodon.h>

namespace {

class RustGlueMastodonPrivate : public MastodonHook {
public:
    // MastodonHook interface
public:
    bool isLoggedIn() const override {
        return false;
    }

    void prepareLogin(const QString &serverUrl, EventBus *bus, EventBus::SendDisplayCodeInputCb cb) override {
        Q_UNUSED(serverUrl)
        cb(bus);
    }
};

} // namespace

std::unique_ptr<MastodonHook> Mastodon::makeHook() {
    return std::make_unique<RustGlueMastodonPrivate>();
}
