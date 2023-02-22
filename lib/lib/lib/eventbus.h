#pragma once

#include <QObject>

class EventBus : public QObject {
    Q_OBJECT
public:
    using SendDisplayCodeInputCb = void (*)(EventBus *bus);
    explicit EventBus(QObject *parent = nullptr);
    static void sendDisplayCodeInput(EventBus *bus);
signals:
    void displayCodeInput();
};
