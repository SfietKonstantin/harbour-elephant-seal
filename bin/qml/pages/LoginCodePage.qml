import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.elephantseal 1.0

Page {
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
                    label: qsTr("Mastodon authentication code")
                }

                Button {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("Login")
                }
            }
        }
    }
}
