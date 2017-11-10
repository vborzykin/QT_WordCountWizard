#ifndef PROGRESS_H
#define PROGRESS_H

#include <QObject>
#include <atomic>

class ProgressStatus : public QObject
{
    Q_OBJECT
    Q_PROPERTY (int minimum READ minimum NOTIFY minimumChanged)
    Q_PROPERTY (int maximum READ maximum NOTIFY maximumChanged)
    Q_PROPERTY (int value READ value NOTIFY valueChanged)
    Q_PROPERTY (int rowsCount READ rowsCount NOTIFY rowsCountChanged)
    Q_PROPERTY (int wordsCount READ wordsCount NOTIFY wordsCountChanged)
    Q_PROPERTY (int uniqWordsCount READ uniqWordsCount NOTIFY uniqWordsCountChanged)

public:
    explicit ProgressStatus(QObject* parent = nullptr);

    int minimum() const {return m_minimum;}
    int maximum() const {return m_maximum;}
    int value() const {return m_value;}
    int rowsCount() const {return m_rowsCount.load();}
    int wordsCount() const {return m_wordsCount.load();}
    int uniqWordsCount() const {return m_uniqWordsCount;}

    void setMinimum(int minimum);
    void setMaximum(int maximum);
    void setValue(int value);

    void resetCounters();
    void incRowsCount();
    void incWordsCount(int count = 1);
    void setUniqWordCount(int count);

signals:
    void minimumChanged(int minimum);
    void maximumChanged(int maximum);
    void valueChanged(int value);
    void rowsCountChanged();
    void wordsCountChanged();
    void uniqWordsCountChanged();

private:
    int m_minimum {0};
    int m_maximum {1};
    int m_value {0};

    std::atomic_int m_rowsCount {0};
    std::atomic_int m_wordsCount {0};
    int m_uniqWordsCount{0};
};

#endif // PROGRESS_H
