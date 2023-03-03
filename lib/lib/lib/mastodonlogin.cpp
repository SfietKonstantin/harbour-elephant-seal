#include "mastodonlogin.h"

#include "eventbus.h"
#include "mastodon.h"

#include <QDesktopServices>
#include <QUrl>

MastodonLogin::MastodonLogin(QObject *parent)
    : QObject(parent)
    , m_preLoginTask(new Task(this))
    , m_loginTask(new Task(this)) //
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
            connect(&bus, &EventBus::preLoginSuccess, this, &MastodonLogin::handlePreLoginSuccess);
            connect(&bus, &EventBus::loginSuccess, m_loginTask, &Task::setSuccess);
            connect(&bus, &EventBus::preLoginError, m_preLoginTask, &Task::setError);
            connect(&bus, &EventBus::loginError, m_loginTask, &Task::setError);
        }
        emit mastodonChanged();
    }
}

Task *MastodonLogin::preLoginTask() const {
    return m_preLoginTask;
}

Task *MastodonLogin::loginTask() const {
    return m_loginTask;
}

void MastodonLogin::preLogin(const QString &server) {
    if (m_mastodon != nullptr) {
        m_preLoginTask->setLoading();
        m_mastodon->preLogin(server);
    }
}

void MastodonLogin::login(const QString &code) {
    if (m_mastodon != nullptr) {
        m_loginTask->setLoading();
        m_mastodon->login(code);
    }
}

void MastodonLogin::handlePreLoginSuccess(const QString &url) {
    m_preLoginTask->setSuccess();
    QDesktopServices::openUrl(QUrl(url));
}
