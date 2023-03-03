import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.elephantseal 1.0
import "../components"

Dialog {
    canAccept: mastodonLogin.preLoginTask.status === Task.Success
               && codeField.text.length > 0
    onAccepted: mastodonLogin.login(codeField.text)
    acceptDestination: loginFinalizationPage

    PageBusyIndicator {
        running: mastodonLogin.preLoginTask.status === Task.Loading
    }

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: content.height
        visible: mastodonLogin.preLoginTask.status === Task.Success

        VerticalScrollDecorator {}
        Column {
            id: content
            anchors.left: parent.left
            anchors.right: parent.right
            spacing: Theme.paddingLarge

            DialogHeader {
                acceptText: qsTr("Login")
            }

            Label {
                anchors.left: parent.left
                anchors.leftMargin: Theme.horizontalPageMargin
                anchors.right: parent.right
                anchors.rightMargin: Theme.horizontalPageMargin
                text: qsTr("Paste the code you received from Mastodon in the field below.")
                wrapMode: Text.WordWrap
                color: Theme.highlightColor
            }

            TextField {
                id: codeField
                anchors.left: parent.left
                anchors.right: parent.right
                label: qsTr("Mastodon login code")
                focus: mastodonLogin.preLoginTask.status === Task.Success
            }
        }
    }

    DialogError {
        visible: mastodonLogin.preLoginTask.status === Task.Error
        context: qsTr("Could not connect to Mastodon instance")
        error: mastodonLogin.preLoginTask.error
        detailedError: mastodonLogin.preLoginTask.detailedError
    }

    Component {
        id: loginFinalizationPage
        LoginFinalizationPage {}
    }
}
