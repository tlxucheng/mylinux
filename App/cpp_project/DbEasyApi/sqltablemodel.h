#pragma once

#ifndef SQLTABLEMODEL_H
#define SQLTABLEMODEL_H

#include <iostream>
#include <string>

using namespace std;

#include "sqlquerymodel.h"
#include "sqltablemodel.h"

class SqlTableModel : public SqlQueryModel
{
public:
	void setTable(const string& tablename);
	string& getTable();
	void setFilter(const string& filter);
	string& getFilter();
	void setQuery(const SqlQuery &query);
	void select();
	string& selectStatement();

	void show();
private:
	string m_tablename;
	string m_filter;
	Sqldatabase db;
};

#endif
