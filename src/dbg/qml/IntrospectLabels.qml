
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

RowLayout {
    spacing: 16

    GridLayout {
        Label {
            text: "PC: "
            font.bold: true
        }
        Label {
            text: machine.pc
            font: fixedFont
        }
    }

    GridLayout {
        Label {
            text: "SP: "
            font.bold: true
        }
        Label {
            text: machine.sp
            font: fixedFont
        }
    }

    GridLayout {
        Label {
            text: "Flags: "
            font.bold: true
        }
        Label {
            text: machine.flags
            font: fixedFont
        }
    }
}
