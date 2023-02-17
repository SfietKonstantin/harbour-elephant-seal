#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <QtQml/qqml.h>
#include <lib/mastodon.h>
#include <lib/mastodonlogin.h>
#include <sailfishapp.h>

int main(int argc, char *argv[]) {
    qmlRegisterType<Mastodon>("harbour.elephantseal", 1, 0, "Mastodon");
    qmlRegisterType<MastodonLogin>("harbour.elephantseal", 1, 0, "MastodonLogin");
    return SailfishApp::main(argc, argv);
}
