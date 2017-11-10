#include "wordcountermodel.h"

WordCounterModel::WordCounterModel(QObject *parent):QAbstractTableModel(parent)
{
}

void WordCounterModel::reset()
{
    emit beginResetModel();
    m_keys.clear();
    emit endResetModel();
    emit layoutChanged();
}

void WordCounterModel::reduce(const WordCount &data)
{
    emit beginResetModel();
    std::lock_guard<std::mutex> lock(m_keys_mutex);
    m_keys.clear();
    emit endResetModel();
    m_keys.reserve(data.size());
    for(const auto it : data)
    {
        m_keys.emplace_back(it.first, it.second);
    }
    insertRows(0, m_keys.size());
}

int WordCounterModel::rowCount(const QModelIndex &parent) const
{
    std::lock_guard<std::mutex> lock(this->m_keys_mutex);
    Q_UNUSED(parent);
    return m_keys.size();
}

int WordCounterModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 2;
}

QVariant WordCounterModel::data(const QModelIndex &index, int role) const
{
    std::lock_guard<std::mutex> lock(m_keys_mutex);
    if(role == WordCounterRoles::WordRole)
    {
        return m_keys[index.row()].first;
    }
    if(role == WordCounterRoles::CountRole)
    {
        return m_keys[index.row()].second;
    }
    return {};
}

QHash<int, QByteArray> WordCounterModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[WordCounterRoles::WordRole] = "word";
    roles[WordCounterRoles::CountRole] = "count";
    return roles;
}
