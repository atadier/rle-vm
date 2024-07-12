
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window

import net.atadier.rlevm

ApplicationWindow {
    id: window
    visible: true
    title: "RLE Machine Debugger" + (editor.isEdited() ? "*" : "")

    GridLayout {
        ColumnLayout {
            spacing: 8
            Layout.margins: 8

            IntrospectLabels {}

            RowLayout {
                spacing: 8

                Button {
                    icon.name: "media-playback-start"
                    text: "Run"
                    onClicked: machine.run()
                }

                Button {
                    icon.name: "bqm-diff"
                    text: "Step"
                    onClicked: machine.step()
                }

                Button {
                    icon.name: "chronometer-reset"
                    text: "Reset"
                    onClicked: machine.reload()
                }

                Button {
                    icon.name: "checkmark"
                    text: "Apply"
                    enabled: editor.isEdited()
                    onClicked: {
                        machine.loadModuleSource(editor.editContent)
                        machine.reload()
                    }
                }
            }

            RowLayout {
                spacing: 8

                ProgramViewer {
                    id: editor
                    content: machine.programSource
                }
            }
        }
    }

    VmController {
        id: machine
        objectName: "vmController"
    }
}
