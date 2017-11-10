#ifndef UTILS_H
#define UTILS_H

#include <QObject>
class QQmlEngine;
class QJSEngine;
class QStringList;

class Utils : public QObject
{
    Q_OBJECT
public:
    explicit Utils(QObject *parent = nullptr);

    static Q_INVOKABLE QString UrlToPath(const QString& url);
};

QStringList splitOnWords(const QString& text);

#endif // UTILS_H
