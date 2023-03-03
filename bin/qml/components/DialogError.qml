import QtQuick 2.0
import Sailfish.Silica 1.0

SilicaFlickable {
    property alias context: item.context
    property alias error: item.error
    property alias detailedError: item.detailedError

    anchors.fill: parent
    contentHeight: content.height

    VerticalScrollDecorator {}
    Column {
        id: content
        anchors.left: parent.left
        anchors.right: parent.right
        spacing: Theme.paddingLarge

        DialogHeader {
            title: qsTr("Error")
        }

        ErrorItem {
            id: item
        }
    }
}
