#include "eventbus.h"

EventBus::EventBus(QObject *parent)
    : QObject(parent) //
{
}

void EventBus::sendPreLoginSuccess(EventBus &bus, const QString &url) {
    emit bus.preLoginSuccess(url);
}

void EventBus::sendLoginSuccess(EventBus &bus) {
    emit bus.loginSuccess();
}

void EventBus::sendPreLoginError(EventBus &bus, LoginErrorType error, const QString &detailedError) {
    emit bus.preLoginError(error, detailedError);
}

void EventBus::sendLoginError(EventBus &bus, LoginErrorType error, const QString &detailedError) {
    emit bus.loginError(error, detailedError);
}
