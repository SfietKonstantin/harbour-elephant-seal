#pragma once

#include <QObject>

class Mastodon;
class MastodonLogin : public QObject {
    Q_OBJECT
    Q_PROPERTY(Mastodon *mastodon READ mastodon WRITE setMastodon NOTIFY mastodonChanged)
    Q_PROPERTY(QString server READ server WRITE setServer NOTIFY serverChanged)

public:
    explicit MastodonLogin(QObject *parent = nullptr);
    Mastodon *mastodon() const;
    void setMastodon(Mastodon *mastodon);
    const QString &server() const;
    void setServer(const QString &server);

public slots:
    void prepareLogin();

signals:
    void mastodonChanged();
    void serverChanged();

    void openCodeUrl(const QString &url);

private:
    Mastodon *m_mastodon{nullptr};
    QString m_server;
};
