#ifndef WORDCOUNTERMODEL_H
#define WORDCOUNTERMODEL_H

#include <QAbstractTableModel>
#include <mutex>

using WordCount = std::map<QString, quint32>;

class WordCounterModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum WordCounterRoles{
        WordRole = Qt::UserRole + 1,
        CountRole
    };
    explicit WordCounterModel(QObject *parent = Q_NULLPTR);
    void reduce(const WordCount& data);
    void reset();

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    std::vector<std::pair<QString, quint32>> m_keys;
    mutable std::mutex m_keys_mutex;
};

#endif // WORDCOUNTERMODEL_H

