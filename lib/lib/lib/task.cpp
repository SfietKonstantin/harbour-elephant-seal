#include "task.h"

Task::Task(QObject *parent)
    : QObject(parent) //
{
}

Task::Status Task::status() const {
    return m_status;
}

const QString &Task::error() const {
    return m_error;
}

const QString &Task::detailedError() const {
    return m_detailedError;
}

void Task::reset() {
    setErrorStatus(QString(), QString());
    setStatus(Ready);
}

void Task::setLoading() {
    setErrorStatus(QString(), QString());
    setStatus(Loading);
}

void Task::setSuccess() {
    setErrorStatus(QString(), QString());
    setStatus(Success);
    emit success();
}

void Task::setError(LoginErrorType error, const QString &detailedError) {
    setErrorStatus(ErrorsTranslator::translateLoginError(error), detailedError);
    setStatus(Error);
}

void Task::setStatus(Status status) {
    if (m_status != status) {
        m_status = status;
        emit statusChanged();
    }
}

void Task::setErrorStatus(const QString &error, const QString &detailedError) {
    if (m_error != error) {
        m_error = error;
        emit errorChanged();
    }

    if (m_detailedError != detailedError) {
        m_detailedError = detailedError;
        emit detailedErrorChanged();
    }
}
