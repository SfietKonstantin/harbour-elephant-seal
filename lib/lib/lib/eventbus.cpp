#include "eventbus.h"

EventBus::EventBus(QObject *parent)
    : QObject(parent) //
{
}

void EventBus::sendDisplayCodeInput(EventBus *bus) {
    emit bus->displayCodeInput();
}
