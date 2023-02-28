#pragma once

#include <QObject>

class EventBus : public QObject {
    Q_OBJECT
public:
    explicit EventBus(QObject *parent = nullptr);
    static void sendOpenCodeUrl(EventBus &bus, const QString &url);
signals:
    void openCodeUrl(const QString &url);
};
