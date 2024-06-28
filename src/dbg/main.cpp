#include <QApplication>
#include <QMainWindow>
#include <QCommandLineParser>

class VirtualDebuggerWindow: public QMainWindow
{

};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setApplicationName("rle-debug");

    QCommandLineParser parser;
    parser.setApplicationDescription("Application debugger for the RLE virtual machine");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("source", "Assembly source code");
    parser.process(a);

    VirtualDebuggerWindow window;
    window.show();
    return QApplication::exec();
}