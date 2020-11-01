#pragma once

#ifndef MYSQLSQLRESULT_H
#define MYSQLSQLRESULT_H

#include <vector>
#include "mysql.h"
#include "MysqlDriver.h"

struct MyFields
{
	string name;
	int type;
};

class MySqlResult
{
public:
	int GetResult(MYSQL *mysql, string& statement);
	int GetFields(MYSQL *mysql, string& tablename);
	vector<MyFields>& getField()
	{
		return m_fields;
	};

private:
	vector<MyFields> m_fields;

	MYSQL_RES        *m_result;
	//MYSQL_FIELD      *m_fields;
	int              m_fields_num;
	vector<string>   m_field_name;
};

#endif