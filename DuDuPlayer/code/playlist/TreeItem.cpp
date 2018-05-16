#include "TreeItem.h"  

TreeItem::TreeItem() :m_parentItem(NULL)
{
}
TreeItem::TreeItem(const QList<QVariant> &data, TreeItem* parent) : m_parentItem(NULL)
{
	m_parentItem = parent;
	m_itemData = data;
}
TreeItem::~TreeItem()
{
	qDeleteAll(m_childItems);
}

void TreeItem::appendChild(TreeItem *item)
{
	item->setParent(this);
	m_childItems.append(item);
}
void TreeItem::deleteAllChild()
{
	for (int index = 0; index < m_childItems.size(); index++)
	{
		m_childItems[index]->deleteAllChild();
	}
	qDeleteAll(m_childItems);
	m_childItems.clear();
}
TreeItem *TreeItem::child(int row)
{
	return m_childItems.value(row);
}
int TreeItem::childCount() const
{
	return m_childItems.count();
}
int TreeItem::columnCount() const
{
	return m_itemData.count();
	//return 1;
}
QVariant TreeItem::data(int column) const
{
	return m_itemData .value(column);
}
TreeItem *TreeItem::parent()
{
	return m_parentItem;
}
void TreeItem::setParent(TreeItem *parent)
{
	m_parentItem = parent;
}
int TreeItem::row() const
{
	if (!m_parentItem) { return 0; }

	return m_parentItem->m_childItems.indexOf(const_cast<TreeItem*>(this));
}