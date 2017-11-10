#ifndef SORTEDMODEL_H
#define SORTEDMODEL_H

#include <QSortFilterProxyModel>

class SortedModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    SortedModel(QObject *parent = Q_NULLPTR);

    // QSortFilterProxyModel interface
protected:
    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const override;
};

#endif // SORTEDMODEL_H
