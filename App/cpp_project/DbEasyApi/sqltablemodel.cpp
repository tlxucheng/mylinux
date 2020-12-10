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
	const string query = selectStatement();

	SqlQuery qu(query, db);

	/* 将字段相关的的存储起来，便于展示的时候使用  */

	return;
}

string& SqlTableModel::selectStatement() /* 用const修饰，怎么编译通过 */
{
	string statement;

	statement.append("select *from ").append(getTable()).append(getFilter());

	return statement;
}

/* 先直接在SqlTableModel类中show，实际需要实现MVC，在view类中show */
void SqlTableModel::show()
{
}