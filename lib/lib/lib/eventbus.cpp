#include "eventbus.h"

EventBus::EventBus(QObject *parent)
    : QObject(parent) //
{
}

void EventBus::sendOpenCodeUrl(EventBus &bus, const QString &url) {
    emit bus.openCodeUrl(url);
}
