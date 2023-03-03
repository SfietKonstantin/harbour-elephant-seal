import QtQuick 2.0
import Sailfish.Silica 1.0

Column {
    id: container
    property alias context: contextLabel.text
    property alias error: errorLabel.text
    property alias detailedError: detailedErrorLabel.text

    anchors.left: parent.left
    anchors.right: parent.right
    spacing: Theme.paddingLarge

    Label {
        id: contextLabel
        anchors.left: parent.left
        anchors.leftMargin: Theme.horizontalPageMargin
        anchors.right: parent.right
        anchors.rightMargin: Theme.horizontalPageMargin
        wrapMode: Text.WordWrap
        color: Theme.errorColor
    }

    Label {
        id: errorLabel
        anchors.left: parent.left
        anchors.leftMargin: Theme.horizontalPageMargin
        anchors.right: parent.right
        anchors.rightMargin: Theme.horizontalPageMargin
        wrapMode: Text.WordWrap
        color: Theme.errorColor
    }

    Button {
        visible: !detailedErrorLabel.visible
        anchors.horizontalCenter: parent.horizontalCenter
        text: qsTr("Show details")
        onClicked: detailedErrorLabel.visible = true
    }

    Label {
        id: detailedErrorLabel
        visible: false
        anchors.left: parent.left
        anchors.leftMargin: Theme.horizontalPageMargin
        anchors.right: parent.right
        anchors.rightMargin: Theme.horizontalPageMargin
        wrapMode: Text.WordWrap
        color: Theme.highlightColor
    }
}
