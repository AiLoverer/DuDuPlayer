#include "TreeModel.h"

TreeModel::TreeModel(QObject *parent) :
QAbstractItemModel(parent), m_rootItem(NULL)
{
	QList<QVariant> listcs;
	listcs.append("ceshi");
	listcs.append("cs");
	m_rootItem = new TreeItem(listcs,NULL);

	QList<QVariant> list;
	list.append("ZhongGuo");
	list.append("ZhG");
	auto item = new TreeItem(list, m_rootItem);
	m_rootItem->appendChild(item);
	
	QList<QVariant> BJ_List;
	BJ_List.append("BeiJing");
	BJ_List.append("BJ");
	auto BJ_Item = new TreeItem(BJ_List, item);
	item->appendChild(BJ_Item);

	QList<QVariant> ShX_List;
	ShX_List.append("ShannXi");
	ShX_List.append("ShX");
	QList<QVariant> XiAn_List;
	XiAn_List.append("XiAn");
	XiAn_List.append("XA");
	QList<QVariant> XiAn_GaoXin_List;
	XiAn_GaoXin_List.append("GaoXin");
	XiAn_GaoXin_List.append("XA_GaoXin");
	auto ShX_Item = new TreeItem(ShX_List, item);
	auto XA_Item = new TreeItem(XiAn_List, ShX_Item);
	auto XA_GX_Item = new TreeItem(XiAn_GaoXin_List, XA_Item);

	item->appendChild(ShX_Item);
	ShX_Item->appendChild(XA_Item);
	XA_Item->appendChild(XA_GX_Item);

	QList<QVariant> GuangDong_List;
	GuangDong_List.append("GuangDong");
	GuangDong_List.append("GD");
	QList<QVariant> DongGuan;
	DongGuan.append("DongGuan");
	DongGuan.append("DG");
	auto GuangDong_Item = new TreeItem(GuangDong_List, item);
	auto DongGuan_Item = new TreeItem(DongGuan, GuangDong_Item);
	item->appendChild(GuangDong_Item);
	GuangDong_Item->appendChild(DongGuan_Item);

	QList<QVariant> ShangHai;
	ShangHai.append("ShangHai");
	ShangHai.append("ShH");
	auto ShangHai_Item = new TreeItem(ShangHai, item);
	item->appendChild(ShangHai_Item);
}

TreeModel::~TreeModel()
{
	delete m_rootItem;
}
void TreeModel::appendChild(const QModelIndex& index)
{
	TreeItem* clickItem = static_cast<TreeItem*>(index.internalPointer());
	/*beginRemoveRows(index, 0, 0);
	clickItem->deleteAllChild();
	endRemoveRows();*/
	removeRows(0, clickItem->childCount(), index);

	QList<QVariant> TestItem;
	TestItem.append("TestItem");
	TestItem.append("TI");
	TreeItem* TestItem_Item = new TreeItem(TestItem, clickItem);

	QList<QVariant> TestItem2;
	TestItem2.append("TestItem2");
	TestItem2.append("TI2");
	TreeItem* TestItem_Item2 = new TreeItem(TestItem2, TestItem_Item);

	beginInsertRows(index, 0, 0);
	TestItem_Item->appendChild(TestItem_Item2);
	clickItem->appendChild(TestItem_Item);
	endInsertRows();
}
bool TreeModel::removeRows(int row, int count, QModelIndex parent)
{
	if (parent.isValid())
	{
		for (int r = row; r < (row + count); ++r)
		{
			QModelIndex idxRemove = parent.child(r, 0);
			TreeItem* fiRemove = static_cast<TreeItem*>(idxRemove.internalPointer());
			if (idxRemove.child(0, 0).isValid())
			{
				bool childRemoved = removeRows(0, fiRemove->childCount(), idxRemove);
			}
		}

		TreeItem* fiParent = static_cast<TreeItem*>(parent.internalPointer());

		int last = 0;
		if (row + count - 1 > 0)
		{
			last = row + count - 1;
		}
		beginRemoveRows(parent, row, last);
		fiParent->deleteAllChild();
		endRemoveRows();
		return true;
	}
	else
	{
		for (int r = row; r < (row + count); ++r)
		{
			TreeItem* slnItem = m_rootItem->child(r);
			bool projectRemoved = removeRows(0, slnItem->childCount(), index(r, 0, QModelIndex()));
		}
		if ((row + count) > 0)
		{
			beginRemoveRows(QModelIndex(), row, row + count - 1);
			m_rootItem->deleteAllChild();
			endRemoveRows();
		}
		return true;
	}
	return false;
}
int TreeModel::columnCount(const QModelIndex &parent) const
{
	return 2;

	//返回实际的列数(实际是他返回了0，因为在创建根目录时用的是无参构造m_rootItem = new TreeItem)，View控件会认为表是空表，不获取数据
	if (parent.isValid())
	{
		return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
	}
	else
	{
		return m_rootItem->columnCount();
	}
}

QHash<int, QByteArray> TreeModel::roleNames() const
{
	QHash<int, QByteArray> names(QAbstractItemModel::roleNames());
	names[NAME] = "name";
	names[SIMPLIFY] = "simplify";
	return names;
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
	{
		return QVariant();
	}

	switch (role)
	{
	case NAME:
	{
				  return static_cast<TreeItem*>(index.internalPointer())->data(0);
	}
	case SIMPLIFY:
	{
				  return static_cast<TreeItem*>(index.internalPointer())->data(1);
 	}
	}
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
	{
		return 0;
	}

	return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
	if (!hasIndex(row, column, parent))
	{
		return QModelIndex();
	}

	TreeItem *parentItem;
	if (!parent.isValid())
	{
		parentItem = m_rootItem;
	}
	else
	{
		parentItem = static_cast<TreeItem*>(parent.internalPointer());
	}

	TreeItem *childItem = parentItem->child(row);
	if (childItem)
	{
		return createIndex(row, column, childItem);
	}
	else
	{
		return QModelIndex();
	}
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
	if (!index.isValid())
	{
		return QModelIndex();
	}

	TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
	TreeItem *parentItem = childItem->parent();

	if (parentItem == m_rootItem)
	{
		return QModelIndex();
	}

	return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
	TreeItem *parentItem;
	if (parent.column() > 0)
	{
		return 0;
	}

	if (!parent.isValid())
	{
		parentItem = m_rootItem;
	}
	else
	{
		parentItem = static_cast<TreeItem*>(parent.internalPointer());
	}

	return parentItem->childCount();
}
