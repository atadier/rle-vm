
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ColumnLayout {
    required property list<int> stack
    required property int sp
    spacing: 2

    Repeater {
        model: Math.min(stack.length, 10)

        Pane {
            id: stackItem
            required property int index

            Layout.minimumWidth: 100

            background: Rectangle {
                color: sp < index ? palette.alternateBase : palette.base;
            }

            Label {
                text: stack[index]
                font: fixedFont
            }
        }
    }
}
