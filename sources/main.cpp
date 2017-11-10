#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "file_analizer/fileanalizer.h"
#include "utils/utils.h"

static QObject* UtilsProvider(QQmlEngine* engine, QJSEngine* scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return new Utils();
}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<FileAnalizer>("Vbor.wordcount.fileanalizer", 1, 0, "FileAnalizer");
    qmlRegisterSingletonType<Utils>("Vbor.wordcount.utils", 1, 0, "Utils", UtilsProvider);

    QQmlApplicationEngine engine;
    FileAnalizer fileAnalizer;
    engine.rootContext()->setContextProperty("fileAnalizer", &fileAnalizer);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
