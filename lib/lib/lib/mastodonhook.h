#pragma once

#include "eventbus.h"

#include <QString>

class Mastodon;
class MastodonHook {
public:
    virtual ~MastodonHook();
    virtual bool isLoggedIn() const = 0;
    virtual void prepareLogin(const QString &serverUrl, EventBus *bus, EventBus::SendDisplayCodeInputCb cb) = 0;

protected:
    explicit MastodonHook();

private:
    MastodonHook(const MastodonHook &other);
    MastodonHook(MastodonHook &&other);
    MastodonHook &operator=(const MastodonHook &other);
    MastodonHook &operator=(MastodonHook &&other);
};
