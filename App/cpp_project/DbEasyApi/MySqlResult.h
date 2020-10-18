#pragma once

#ifndef MYSQLSQLRESULT_H
#define MYSQLSQLRESULT_H

#include <vector>
#include "mysql.h"
#include "MysqlDriver.h"

class MySqlResult
{
public:
	int GetResult(MYSQL *mysql, string& statement);

	struct MyFileds
	{
		
	};

private:

	MYSQL_RES        *m_result;
	MYSQL_FIELD      *m_fields;
	int              m_fields_num;
	vector<string>   m_field_name;
};

#endif