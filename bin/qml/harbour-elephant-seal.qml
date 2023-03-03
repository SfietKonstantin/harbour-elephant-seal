import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.elephantseal 1.0
import "pages"

ApplicationWindow {
    initialPage: root.loggedIn ? mainPage : loginPage

    // cover: Qt.resolvedUrl("cover/CoverPage.qml")
    allowedOrientations: defaultAllowedOrientations

    Mastodon {
        id: root
    }

    Component {
        id: mainPage
        MainPage {}
    }

    Component {
        id: loginPage
        LoginPage {}
    }
}
