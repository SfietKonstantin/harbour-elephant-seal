#pragma once

#include <QObject>

class AsyncBus : public QObject {
    Q_OBJECT
public:
    using SendDisplayCodeInputCb = void (*)(AsyncBus *bus);
    explicit AsyncBus(QObject *parent = nullptr);
    static void sendDisplayCodeInput(AsyncBus *bus);
signals:
    void displayCodeInput();
};
