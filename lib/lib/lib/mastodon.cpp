#include "mastodon.h"

Mastodon::Mastodon(QObject *parent)
    : QObject(parent)
    , m_hook(makeHook())
    , m_asyncBus(new AsyncBus(this)) //
{
    Q_ASSERT(m_hook != nullptr);
    m_loggedIn = m_hook->isLoggedIn();
}

bool Mastodon::isLoggedIn() const {
    return m_loggedIn;
}

AsyncBus *Mastodon::asyncBus() const {
    return m_asyncBus;
}

void Mastodon::prepareLogin(const QString &server) {
    m_hook->prepareLogin(server, m_asyncBus, &AsyncBus::sendDisplayCodeInput);
}

void Mastodon::setLoggedIn(bool loggedIn) {
    if (m_loggedIn != loggedIn) {
        m_loggedIn = loggedIn;
        emit loggedInChanged();
    }
}
