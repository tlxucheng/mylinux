#include "stdafx.h"
#include "sqltablemodel.h"

SqlTableModel::SqlTableModel()
{
	string dbtype = "MYSQL";
	m_db = m_db.getDatabase(dbtype);
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

	SqlQuery qu(query, m_db);

	/* ���ֶ���صĵĴ洢����������չʾ��ʱ��ʹ��  */
	setQuery(qu);

	return;
}

string SqlTableModel::selectStatement() /* ��const���Σ���ô����ͨ�� */
{
	string statement;

	statement.append("select *from ").append(getTable()).append(getFilter());

	cout << "statement: " << statement << endl;

	return statement;
}

/* ��ֱ����SqlTableModel����show��ʵ����Ҫʵ��MVC����view����show */
void SqlTableModel::show()
{
	query.getSqlResult()->show_fileds_type();

	int index = 0;
	query.getSqlResult()->show_data(0);

}