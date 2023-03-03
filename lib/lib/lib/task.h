#pragma once

#include "errors.h"

class Task : public QObject {
    Q_OBJECT
    Q_PROPERTY(Status status READ status NOTIFY statusChanged)
    Q_PROPERTY(QString error READ error NOTIFY errorChanged)
    Q_PROPERTY(QString detailedError READ detailedError NOTIFY detailedErrorChanged)

public:
    enum Status {
        Ready,
        Loading,
        Success,
        Error
    };
    Q_ENUM(Status)

    explicit Task(QObject *parent = nullptr);
    Status status() const;
    const QString &error() const;
    const QString &detailedError() const;

    void reset();
    void setLoading();
    void setSuccess();
    void setError(LoginErrorType error, const QString &detailedError);

signals:
    void success();

    void statusChanged();
    void errorChanged();
    void detailedErrorChanged();

private:
    void setStatus(Status status);
    void setErrorStatus(const QString &error, const QString &detailedError);

    Status m_status{Ready};
    QString m_error;
    QString m_detailedError;
};
