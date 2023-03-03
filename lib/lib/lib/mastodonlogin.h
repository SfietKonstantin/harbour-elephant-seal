#pragma once

#include "task.h"

class Mastodon;
class MastodonLogin : public QObject {
    Q_OBJECT
    Q_PROPERTY(Mastodon *mastodon READ mastodon WRITE setMastodon NOTIFY mastodonChanged)
    Q_PROPERTY(Task *preLoginTask READ preLoginTask CONSTANT)
    Q_PROPERTY(Task *loginTask READ loginTask CONSTANT)

public:
    enum Status {
        Loading,
        Success,
        Error
    };
    Q_ENUM(Status)

    explicit MastodonLogin(QObject *parent = nullptr);
    Mastodon *mastodon() const;
    void setMastodon(Mastodon *mastodon);
    Task *preLoginTask() const;
    Task *loginTask() const;

public slots:
    void preLogin(const QString &server);
    void login(const QString &code);

signals:
    void mastodonChanged();

private:
    void handlePreLoginSuccess(const QString &url);

    Mastodon *m_mastodon{nullptr};
    Task *m_preLoginTask{nullptr};
    Task *m_loginTask{nullptr};
};
