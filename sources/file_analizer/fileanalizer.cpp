#include "fileanalizer.h"
#include <QUrl>
#include <QFile>
#include <QTextStream>
#include <QtConcurrent>
#include "../utils/utils.h"

FileAnalizer::FileAnalizer(QObject* parent) : QObject(parent)
{
    connect(&m_watcher, &FutureWatcher::finished, [this](){if(!m_watcher.isCanceled())emit finished();});
    connect(&m_watcher, &FutureWatcher::progressRangeChanged,
            [this](int min, int max){m_progressStatus.setMinimum(min);m_progressStatus.setMaximum(max);});
    connect(&m_watcher, &FutureWatcher::progressValueChanged, &m_progressStatus, &ProgressStatus::setValue);

    m_sortedmodel.setSourceModel(&m_model);
    m_sortedmodel.sort(1, Qt::SortOrder::DescendingOrder);
}

void FileAnalizer::checkFile(const QString& path)
{
    setFileChecked(QFile::exists(path));
}

void FileAnalizer::fileProcess(const QString &path)
{
    m_canceling = false;
    m_progressStatus.resetCounters();
    m_model.reset();

    QFile m_file(path);
    m_file.open(QIODevice::ReadOnly);
    auto size = m_file.size();
    auto nRanges = QThread::idealThreadCount()*10;
    qint64 blockize = size / nRanges;
    QList<Range> ranges;
    QTextStream textStream(&m_file);
    qint64 end{0};
    for(int i = 0; i < nRanges; ++i)
    {
        qint64 start = end;
        end = (i+1) * blockize;
        textStream.seek(end);
        end = textStream.pos();
        ranges.push_back(Range{start, end});
    }
    ranges.last().second = size;

   m_watcher.setFuture(QtConcurrent::mappedReduced
                  <WordCount, QList<Range>,
                  std::function<WordCount(const Range&)>,
                  std::function<void(WordCount&, const WordCount&)>>
                  (ranges,
                    [path, this](const Range& range)
                    {
                        WordCount map;
                        if(m_canceling)
                        {
                            return map;
                        }

                        QFile file(path);
                        file.open(QIODevice::ReadOnly);
                        QTextStream textStream(&file);
                        textStream.seek(range.first);

                        while(!textStream.atEnd() && textStream.pos() < range.second)
                        {
                            auto words = splitOnWords(textStream.readLine());
                            for(const auto& word: words)
                            {
                                map[word] += 1;
                            }
                            if(m_canceling)
                            {
                                return map;
                            }
                            m_progressStatus.incRowsCount();
                            m_progressStatus.incWordsCount(words.size());
                        }
                        return map;
                    },
                    [this](WordCount& uniqWords, const WordCount& words)
                    {
                        if(m_canceling)
                            return;

                        for(const auto word : words)
                        {
                            uniqWords[word.first] += word.second;
                        }
                        reduce(uniqWords);
                        if(!m_canceling)
                        {
                            m_progressStatus.setUniqWordCount(uniqWords.size());
                        }
                    }));
}

void FileAnalizer::cancel()
{
    m_canceling = true;
    m_watcher.cancel();
}

void FileAnalizer::setFileChecked(bool newValue)
{
    if(m_allowProcess != newValue)
    {
        m_allowProcess = newValue;
        emit fileCheckedChanged(m_allowProcess);
    }
}

void FileAnalizer::reduce(const WordCount &data)
{
    m_model.reduce(data);
}
