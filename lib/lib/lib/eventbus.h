#pragma once

#include <QObject>

class EventBus : public QObject {
    Q_OBJECT
public:
    explicit EventBus(QObject *parent = nullptr);
    static void sendDisplayCodeInput(EventBus &bus);
signals:
    void displayCodeInput();
};
