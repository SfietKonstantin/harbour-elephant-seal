#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <QtQml/qqml.h>
#include <lib/lib.h>
#include <sailfishapp.h>

int main(int argc, char *argv[]) {
    qmlRegisterType<Mastodon>("harbour.elephantseal", 1, 0, "Mastodon");
    return SailfishApp::main(argc, argv);
}
