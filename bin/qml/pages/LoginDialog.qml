import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog {
    canAccept: serverField.text.length > 0
    onAccepted: mastodonLogin.preLogin(serverField.text)
    acceptDestination: loginCodeDialog

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: content.height

        VerticalScrollDecorator {}
        Column {
            id: content
            anchors.left: parent.left
            anchors.right: parent.right
            spacing: Theme.paddingLarge

            DialogHeader {
                acceptText: qsTr("Open browser")
            }

            Label {
                anchors.left: parent.left
                anchors.leftMargin: Theme.horizontalPageMargin
                anchors.right: parent.right
                anchors.rightMargin: Theme.horizontalPageMargin
                text: qsTr("Enter your Mastodon instance, then accept this dialog to open the Mastodon login page.")
                wrapMode: Text.WordWrap
                color: Theme.highlightColor
            }

            TextField {
                id: serverField
                anchors.left: parent.left
                anchors.right: parent.right
                label: qsTr("Mastodon instance URL")
                focus: true
            }
        }
    }

    Component {
        id: loginCodeDialog
        LoginCodeDialog {}
    }
}
