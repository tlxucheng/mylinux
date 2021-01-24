#pragma once

#ifndef SQLITERESULT_H
#define SQLITERESULT_H

#include <vector>
#include "sqldatabase.h"

using namespace std;

class SqliteResult : public SqlResult
{
public:
	SqliteResult();
	SqliteResult(Sqldatabase &db);

	bool reset(const string& sqlquery);
	AnyType data(int field);

    void show_fileds_type();
	void show_data(int index);

	int get_fileds_type(const string& query);
private:
	shared_ptr<SqlDriver> m_driver;  /* 是否正确？怎么使用最好？*/

	vector<MyFields> m_fields;

};


#endif