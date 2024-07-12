#include <QApplication>
#include <QCommandLineParser>
#include <QQmlApplicationEngine>
#include <QFontDatabase>
#include <QQmlContext>
#include <QFile>
#include <QQuickWindow>

#include "controller.hpp"

using namespace Qt::StringLiterals;

int main(int argc, char *argv[])
{
    const QApplication app(argc, argv);
    QGuiApplication::setApplicationName("rle-debug");

    QCommandLineParser parser;
    parser.setApplicationDescription("Application debugger for the RLE virtual machine");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("source", "Assembly source code");
    parser.process(app);

    QString source_path = parser.positionalArguments().at(0);
    QFile file(source_path);
    if(!file.open(QIODevice::ReadOnly)) {
        qFatal() << "could not open source file: " << file.errorString();
        return 1;
    }

    QTextStream in(&file);
    const QString source = in.readAll();

    qmlRegisterType<VmController>("net.atadier.rlevm", 1, 0, "VmController");

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/qml/main.qml"_s);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject *obj, const QUrl &objectUrl) {
            if (!obj && url != objectUrl) QCoreApplication::exit(-1);
        }
    );

    const QFont fixedFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    engine.rootContext()->setContextProperty("fixedFont", fixedFont);
    engine.load(url);

    auto *window = qobject_cast<QQuickWindow*>(engine.rootObjects().value(0));
    if (!window) {
        qFatal() << "App did not start, exiting." << Qt::endl;
        return 1;
    }
    auto *controller = window->findChild<VmController*>("vmController");
    controller->loadModuleSource(source);

    return QGuiApplication::exec();
}
