#ifndef TREEMODEL_H  
#define TREEMODEL_H  

// Qt lib import  
#include <QObject>  
#include <QAbstractItemModel>  
#include <QDebug>  

#include "TreeItem.h" 

class TreeModel : public QAbstractItemModel
{
	Q_OBJECT
	enum ItemRoles {
		NAME = Qt::UserRole + 1,
		SIMPLIFY
	};
public:
	TreeModel(QObject *parent = NULL);
	~TreeModel();

	void appendChild(const QModelIndex& index);
	bool removeRows(int row, int count, QModelIndex parent);

	QModelIndex parent(const QModelIndex &index) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;
	QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role) const;
	QHash<int, QByteArray> roleNames() const;

private:
	TreeItem *m_rootItem;
};

#endif // TREEMODEL_H  