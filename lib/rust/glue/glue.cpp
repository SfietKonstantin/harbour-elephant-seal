#include <lib/mastodon.h>

#include <cxx-qt-lib/qstring.h>
#include <elephant-seal-rs/src/ffi.rs.h>

void event_bus_send_display_code_input(EventBus &bus) {
    EventBus::sendDisplayCodeInput(bus);
}

namespace {

using namespace rust::cxxqtlib1;

class RustGlueMastodonPrivate : public MastodonHook {
public:
    // MastodonHook interface
public:
    explicit RustGlueMastodonPrivate()
        : m_rustMastodon(rust_mastodon_new()) //
    {
    }

    bool isLoggedIn() const override {
        return false;
    }

    void prepareLogin(const QString &serverUrl, EventBus &bus) override {
        auto rustServerUrl = qstringToRustString(serverUrl);
        rust_mastodon_prepare_login(*m_rustMastodon, rustServerUrl, bus);
    }

private:
    rust::Box<RustMastodon> m_rustMastodon;
};

} // namespace

std::unique_ptr<MastodonHook> Mastodon::makeHook() {
    return std::make_unique<RustGlueMastodonPrivate>();
}
