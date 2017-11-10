#ifndef FILEANALIZER_H
#define FILEANALIZER_H

#include <QObject>
#include <QFutureWatcher>
#include "progressstatus.h"
#include "../models/wordcountermodel.h"
#include "../models/sortedmodel.h"

class QQmlEngine;
class QJSEngine;

class FileAnalizer : public QObject
{
    Q_OBJECT
    Q_PROPERTY (bool fileChecked READ fileChecked NOTIFY fileCheckedChanged)
    Q_PROPERTY (ProgressStatus* progressStatus READ progressStatus NOTIFY progressStatusChanged)
    Q_PROPERTY (QSortFilterProxyModel* sortedModel READ sortedModel NOTIFY sortedModelChanged)


    using Range = std::pair<qint64, qint64>;
    using FutureWatcher = QFutureWatcher<WordCount>;

public:
    explicit FileAnalizer(QObject* parent = nullptr);

    Q_INVOKABLE void checkFile(const QString& path);
    Q_INVOKABLE void fileProcess(const QString& path);
    Q_INVOKABLE void cancel();
    Q_INVOKABLE bool isRunning(){return m_watcher.isRunning();}

    bool fileChecked(){return m_allowProcess;}
    ProgressStatus* progressStatus(){return &m_progressStatus;}
    QSortFilterProxyModel* sortedModel(){return &m_sortedmodel;}

signals:
    void fileCheckedChanged(bool newValue);
    void finished();
    void progressStatusChanged();
    void sortedModelChanged();

public slots:
    void setFileChecked(bool newValue);
private:
    void reduce(const WordCount& data);
private:
    bool m_allowProcess {false};
    FutureWatcher m_watcher;
    ProgressStatus m_progressStatus {this};
    WordCounterModel m_model {this};
    SortedModel m_sortedmodel;
    WordCount m_data;
    std::atomic_bool m_canceling{false};
};

#endif // FILEANALIZER_H
