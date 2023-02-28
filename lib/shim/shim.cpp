#include <lib/mastodon.h>

namespace {

class ShimMastodonPrivate : public MastodonHook {
public:
    // MastodonHook interface
public:
    bool isLoggedIn() const override {
        return false;
    }

    void prepareLogin(const QString &serverUrl, EventBus &bus) override {
        Q_UNUSED(serverUrl)
        EventBus::sendOpenCodeUrl(bus, serverUrl);
    }
};

} // namespace

std::unique_ptr<MastodonHook> Mastodon::makeHook() {
    return std::make_unique<ShimMastodonPrivate>();
}
