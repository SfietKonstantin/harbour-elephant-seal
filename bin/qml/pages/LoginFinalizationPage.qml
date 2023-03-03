import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.elephantseal 1.0
import "../components"

Page {
    PageBusyIndicator {
        running: mastodonLogin.loginTask.status === Task.Loading
    }

    PageError {
        visible: mastodonLogin.loginTask.status === Task.Error
        context: qsTr("Could not connect to Mastodon instance")
        error: mastodonLogin.loginTask.error
        detailedError: mastodonLogin.loginTask.detailedError
    }

    Connections {
        target: mastodonLogin.loginTask
        onSuccess: pageStack.replaceAbove(null, mainPage)
    }
}
