#include <QGuiApplication>
#include <QCommandLineParser>
#include <QQmlApplicationEngine>

using namespace Qt::StringLiterals;

int main(int argc, char *argv[])
{
    const QGuiApplication app(argc, argv);
    QGuiApplication::setApplicationName("rle-debug");

    QCommandLineParser parser;
    parser.setApplicationDescription("Application debugger for the RLE virtual machine");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("source", "Assembly source code");
    parser.process(app);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/qml/main.qml"_s);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app,
    [url](QObject *obj, const QUrl &objectUrl) {
        if (!obj && url != objectUrl) QCoreApplication::exit(-1);
    }
    );
    engine.load(url);

    return QGuiApplication::exec();
}
