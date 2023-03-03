#include "mastodon.h"

Mastodon::Mastodon(QObject *parent)
    : QObject(parent)
    , m_hook(makeHook())
    , m_eventBus(new EventBus(this)) //
{
    Q_ASSERT(m_hook != nullptr);
    m_loggedIn = m_hook->isLoggedIn();
}

bool Mastodon::isLoggedIn() const {
    return m_loggedIn;
}

EventBus &Mastodon::eventBus() const {
    return *m_eventBus;
}

void Mastodon::preLogin(const QString &server) {
    m_hook->preLogin(server, *m_eventBus);
}

void Mastodon::login(const QString &code) {
    m_hook->login(code, *m_eventBus);
}

void Mastodon::setLoggedIn(bool loggedIn) {
    if (m_loggedIn != loggedIn) {
        m_loggedIn = loggedIn;
        emit loggedInChanged();
    }
}
