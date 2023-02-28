#pragma once

#include <QString>

class EventBus;

void event_bus_send_open_code_url(EventBus &bus, const QString &url);
