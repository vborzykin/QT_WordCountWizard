#include "sortedmodel.h"
#include "wordcountermodel.h"

SortedModel::SortedModel(QObject *parent): QSortFilterProxyModel(parent)
{
}

bool SortedModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
{
    auto left = sourceModel()->data(source_left, WordCounterModel::WordCounterRoles::CountRole).toInt();
    auto right = sourceModel()->data(source_right, WordCounterModel::WordCounterRoles::CountRole).toInt();
    return left < right;
}
