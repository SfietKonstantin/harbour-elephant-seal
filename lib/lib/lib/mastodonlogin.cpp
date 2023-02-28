#include "mastodonlogin.h"

#include "eventbus.h"
#include "mastodon.h"

MastodonLogin::MastodonLogin(QObject *parent)
    : QObject(parent) //
{
}

Mastodon *MastodonLogin::mastodon() const {
    return m_mastodon;
}

void MastodonLogin::setMastodon(Mastodon *mastodon) {
    if (m_mastodon != mastodon) {
        if (m_mastodon != nullptr) {
            auto &bus = m_mastodon->eventBus();
            disconnect(&bus, nullptr, this, nullptr);
        }

        m_mastodon = mastodon;

        if (mastodon != nullptr) {
            auto &bus = mastodon->eventBus();
            connect(&bus, &EventBus::openCodeUrl, this, &MastodonLogin::openCodeUrl);
        }
        emit mastodonChanged();
    }
}

const QString &MastodonLogin::server() const {
    return m_server;
}

void MastodonLogin::setServer(const QString &server) {
    if (m_server != server) {
        m_server = server;
        emit serverChanged();
    }
}

void MastodonLogin::prepareLogin() {
    if (m_mastodon != nullptr) {
        m_mastodon->prepareLogin(m_server);
    }
}
