#ifndef LIBRARYTREEMODEL_H
#define LIBRARYTREEMODEL_H

#include "ItemController.h"
#include <QAbstractItemModel>

class LibraryTreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit LibraryTreeModel(ItemController& itemController, QObject *parent = 0);
    ~LibraryTreeModel();
    QVariant data(const QModelIndex& index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QModelIndex index(int row, int column, const QModelIndex& parent) const;
    QModelIndex parent(const QModelIndex& child) const;
    int rowCount(const QModelIndex& parent) const;
    int columnCount(const QModelIndex& parent) const;
signals:
    
public slots:
    
private:
    ItemController& itemController_;
};

#endif // LIBRARYTREEMODEL_H
