#pragma once

#include "asyncbus.h"

#include <QString>

class Mastodon;
class MastodonHook {
public:
    virtual ~MastodonHook();
    virtual bool isLoggedIn() const = 0;
    virtual void prepareLogin(const QString &serverUrl, AsyncBus *bus, AsyncBus::SendDisplayCodeInputCb cb) = 0;

protected:
    explicit MastodonHook();

private:
    MastodonHook(const MastodonHook &other);
    MastodonHook(MastodonHook &&other);
    MastodonHook &operator=(const MastodonHook &other);
    MastodonHook &operator=(MastodonHook &&other);
};
