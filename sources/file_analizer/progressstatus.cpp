#include "progressstatus.h"

ProgressStatus::ProgressStatus(QObject* parent): QObject(parent)
{

}

void ProgressStatus::setMinimum(int minimum)
{
    if(m_minimum != minimum)
    {
        m_minimum = minimum;
        emit minimumChanged(m_minimum);
    }
}

void ProgressStatus::setMaximum(int maximum)
{
    if(m_maximum != maximum)
    {
        m_maximum = maximum;
        emit maximumChanged(m_maximum);
    }
}

void ProgressStatus::setValue(int value)
{
    if(m_value != value)
    {
        m_value = value;
        emit valueChanged(m_value);
    }
}

void ProgressStatus::resetCounters()
{
    setValue(0);
    m_rowsCount.exchange(0);
    emit rowsCountChanged();
    m_wordsCount.exchange(0);
    emit wordsCountChanged();
    m_uniqWordsCount = 0;
}

void ProgressStatus::incRowsCount()
{
    m_rowsCount++;
    emit rowsCountChanged();
}

void ProgressStatus::incWordsCount(int count)
{
    m_wordsCount += count;
    emit wordsCountChanged();
}

void ProgressStatus::setUniqWordCount(int count)
{
    m_uniqWordsCount = count;
    emit uniqWordsCountChanged();
}
