#pragma once

#include "eventbus.h"
#include "mastodonhook.h"

#include <QObject>
#include <QtQml/QQmlParserStatus>

#include <memory>

class Mastodon : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool loggedIn READ isLoggedIn NOTIFY loggedInChanged)

public:
    explicit Mastodon(QObject *parent = nullptr);
    bool isLoggedIn() const;

    EventBus &eventBus() const;
    void preLogin(const QString &server);
    void login(const QString &code);
signals:
    void loggedInChanged();

private:
    static std::unique_ptr<MastodonHook> makeHook();
    void setLoggedIn(bool loggedIn);

    std::unique_ptr<MastodonHook> m_hook;
    EventBus *m_eventBus{nullptr};
    bool m_loggedIn{false};
};
