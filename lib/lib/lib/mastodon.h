#pragma once

#include "asyncbus.h"
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

    AsyncBus *asyncBus() const;
    void prepareLogin(const QString &server);
signals:
    void loggedInChanged();

private:
    static std::unique_ptr<MastodonHook> makeHook();
    void setLoggedIn(bool loggedIn);

    std::unique_ptr<MastodonHook> m_hook;
    AsyncBus *m_asyncBus{nullptr};
    bool m_loggedIn{false};
};
