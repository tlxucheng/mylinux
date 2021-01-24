#pragma once

#ifndef SQLITERESULT_H
#define SQLITERESULT_H

#include <vector>
#include <string>
#include "sqldatabase.h"

using namespace std;

class SqliteResult : public SqlResult
{
public:
	SqliteResult();
	SqliteResult(Sqldatabase &db);

	bool reset(const string& sqlquery);
	AnyType data(int field);

    void show_fileds();
	void show_data(int index);
	void show_data();

	int get_fileds_type(const string& query);
private:
	shared_ptr<SqlDriver> m_driver;  /* �Ƿ���ȷ����ôʹ����ã�*/

	vector<MyFields> m_fields;
	vector<string> m_values;
	int            m_fields_count;  /* ����sql���仯 */
};


#endif