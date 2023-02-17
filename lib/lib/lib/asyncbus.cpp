#include "asyncbus.h"

AsyncBus::AsyncBus(QObject *parent)
    : QObject(parent) //
{
}

void AsyncBus::sendDisplayCodeInput(AsyncBus *bus) {
    emit bus->displayCodeInput();
}
