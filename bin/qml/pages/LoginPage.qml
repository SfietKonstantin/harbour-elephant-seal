import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.elephantseal 1.0

Page {
    MastodonLogin {
        id: login
        mastodon: mastodonInstance
        onDisplayCodeInput: pageStack.push(codePage)
    }

    SilicaFlickable {
        anchors.fill: parent

        contentHeight: content.height

        Column {
            id: content

            anchors.left: parent.left
            anchors.right: parent.right
            spacing: Theme.paddingLarge
            PageHeader {
                title: qsTr("Elephant seal")
            }

            Column {
                anchors.left: parent.left
                anchors.right: parent.right

                TextField {
                    label: qsTr("Mastodon instance URL")
                    onTextChanged: login.server = text
                }

                Button {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("Authenticate in browser")
                    onClicked: login.prepareLogin()
                }
            }
        }
    }

    Component {
        id: codePage
        LoginCodePage {}
    }
}
