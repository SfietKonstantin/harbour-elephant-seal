import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.elephantseal 1.0

Page {
    id: loginPage
    MastodonLogin {
        id: mastodonLogin
        mastodon: root
    }

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: content.height

        VerticalScrollDecorator {}
        Column {
            id: content
            anchors.left: parent.left
            anchors.right: parent.right
            spacing: Theme.paddingLarge

            PageHeader {
                title: qsTr("Elephant seal")
            }

            Label {
                anchors.left: parent.left
                anchors.leftMargin: Theme.horizontalPageMargin
                anchors.right: parent.right
                anchors.rightMargin: Theme.horizontalPageMargin
                text: qsTr("Log into a Mastodon instance")
                wrapMode: Text.WordWrap
                color: Theme.highlightColor
            }

            Button {
                id: loginButton
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Login")
                onClicked: pageStack.push(loginDialog)
            }
        }
    }

    Component {
        id: loginDialog
        LoginDialog {}
    }
}
