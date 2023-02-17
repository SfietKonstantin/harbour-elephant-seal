#include <lib/mastodon.h>

namespace {

class ShimMastodonPrivate : public MastodonHook {
public:
    // MastodonHook interface
public:
    bool isLoggedIn() const {
        return false;
    }

    void prepareLogin(const QString &serverUrl, AsyncBus *bus, AsyncBus::SendDisplayCodeInputCb cb) {
        cb(bus);
    }
};

} // namespace

std::unique_ptr<MastodonHook> Mastodon::makeHook() {
    return std::make_unique<ShimMastodonPrivate>();
}
