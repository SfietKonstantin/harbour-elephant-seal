#pragma once

#include <QObject>

class Mastodon : public QObject {
    Q_OBJECT
public:
    explicit Mastodon(QObject *parent = nullptr);
};
