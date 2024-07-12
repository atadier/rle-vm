
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Pane {
    required property string content
    property alias editContent: sourceEditor.text

    function isEdited() {
        return content !== editContent;
    }

    background: Rectangle {
        color: isEdited() ? palette.alternateBase : palette.base;
        border.width: 1
        border.color: palette.shadow
        radius: 2
    }

    TextEdit {
        id: sourceEditor
        anchors.fill: parent
        color: palette.text
        font: fixedFont
        wrapMode: TextEdit.NoWrap
        text: content
        focus: true
    }
}
