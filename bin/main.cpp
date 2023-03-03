#include <QtQml/qqml.h>
#include <lib/mastodon.h>
#include <lib/mastodonlogin.h>

#ifdef WITH_SAILFISH
#include <sailfishapp.h>
#endif

int main(int argc, char *argv[]) {
    qmlRegisterType<Mastodon>("harbour.elephantseal", 1, 0, "Mastodon");
    qmlRegisterType<MastodonLogin>("harbour.elephantseal", 1, 0, "MastodonLogin");
    qmlRegisterUncreatableType<Task>("harbour.elephantseal", 1, 0, "Task", "Cannot be created");

#ifdef WITH_SAILFISH
    return SailfishApp::main(argc, argv);
#else
    Q_UNUSED(argc)
    Q_UNUSED(argv)
    return 0;
#endif
}
