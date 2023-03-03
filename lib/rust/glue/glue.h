#pragma once

#include <QString>
#include <lib/errors.h>

class EventBus;

void event_bus_send_pre_login_success(EventBus &bus, const QString &url);
void event_bus_send_login_success(EventBus &bus);
void event_bus_send_pre_login_error(EventBus &bus, LoginErrorType error, const QString &detailedError);
void event_bus_send_login_error(EventBus &bus, LoginErrorType error, const QString &detailedError);
