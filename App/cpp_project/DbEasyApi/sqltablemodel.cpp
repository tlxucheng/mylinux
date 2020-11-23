#include "stdafx.h"
#include "sqltablemodel.h"

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
	/* 实现 QSqlQuery qu(query, d->db); */

	return;
}

string& SqlTableModel::selectStatement() /* 用const修饰，怎么编译通过 */
{
	string statement;

	statement.append("select *from ").append(getTable()).append(getFilter());

	return statement;
}
