#pragma once

#include <QObject>

enum class LoginErrorType : uint8_t {
    IllegalState,
    Url,
    Http,
};

class ErrorsTranslator : public QObject {
    Q_OBJECT
    Q_ENUM(LoginErrorType)
public:
    static QString translateLoginError(LoginErrorType error);

private:
    explicit ErrorsTranslator();
};
