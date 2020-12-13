#include "stdafx.h"
#include "sqltablemodel.h"

SqlTableModel::SqlTableModel()
{

}

void SqlTableModel::setTable(const string& tablename)
{
	m_tablename = tablename;

	return;
}

string& SqlTableModel::getTable()
{
	return m_tablename;
}

void SqlTableModel::setFilter(const string& filter)
{
	m_filter = filter;

	return;
}

string& SqlTableModel::getFilter()
{
	return m_filter;
}

void SqlTableModel::setQuery(const SqlQuery &query)
{
	this->query = query;

	return;
}

void SqlTableModel::select()
{
	const string query = selectStatement();

	SqlQuery qu(query, db);

	/* ���ֶ���صĵĴ洢����������չʾ��ʱ��ʹ��  */
	setQuery(qu);

	return;
}

string& SqlTableModel::selectStatement() /* ��const���Σ���ô����ͨ�� */
{
	string statement;

	statement.append("select *from ").append(getTable()).append(getFilter());

	return statement;
}

/* ��ֱ����SqlTableModel����show��ʵ����Ҫʵ��MVC����view����show */
void SqlTableModel::show()
{
}