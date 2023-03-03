#pragma once

#include "eventbus.h"

#include <QString>

class Mastodon;
class MastodonHook {
public:
    virtual ~MastodonHook();
    virtual bool isLoggedIn() const = 0;
    virtual void preLogin(const QString &serverUrl, EventBus &bus) = 0;
    virtual void login(const QString &code, EventBus &bus) = 0;

protected:
    explicit MastodonHook();

private:
    MastodonHook(const MastodonHook &other);
    MastodonHook(MastodonHook &&other);
    MastodonHook &operator=(const MastodonHook &other);
    MastodonHook &operator=(MastodonHook &&other);
};
