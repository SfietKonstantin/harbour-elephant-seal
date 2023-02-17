import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.elephantseal 1.0
import "pages"

ApplicationWindow {
    initialPage: Component {
        LoginPage {}
    }
    // cover: Qt.resolvedUrl("cover/CoverPage.qml")
    allowedOrientations: defaultAllowedOrientations

    Mastodon {
        id: mastodonInstance
    }
}
