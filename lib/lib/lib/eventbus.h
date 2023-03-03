#pragma once

#include "errors.h"
#include <QObject>

class EventBus : public QObject {
    Q_OBJECT
public:
    explicit EventBus(QObject *parent = nullptr);
    static void sendPreLoginSuccess(EventBus &bus, const QString &url);
    static void sendLoginSuccess(EventBus &bus);
    static void sendPreLoginError(EventBus &bus, LoginErrorType error, const QString &detailedError);
    static void sendLoginError(EventBus &bus, LoginErrorType error, const QString &detailedError);
signals:
    void preLoginSuccess(const QString &url);
    void loginSuccess();
    void preLoginError(LoginErrorType error, const QString &detailedError);
    void loginError(LoginErrorType error, const QString &detailedError);
};
