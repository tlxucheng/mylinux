#pragma once

#ifndef MYSQLSQLRESULT_H
#define MYSQLSQLRESULT_H

#include <vector>
#include "mysql.h"
#include "MysqlDriver.h"
#include "Sqlresult.h"
#include "sqldatabase.h"

class MySqlResult : public SqlResult
{
public:
	MySqlResult();
	MySqlResult(Sqldatabase &db);
	MYSQL_RES* GetResult(MYSQL *mysql, string& statement);
	int GetFields(MYSQL *mysql, string& tablename);
	vector<MyFields>& getField();
	void setField(vector<MyFields>& fields);

	bool reset(const string& query); /* 查询字段和具体数据，字段赋值到fields里面 */
	AnyType data(int filed);

	/* test function */
	void show_fileds();
	void show_data(int index);
	void show_data();
private:
	vector<MyFields> m_fields;

	MYSQL_RES        *m_result;
	MYSQL_ROW        m_row;
	//MysqlDriver      *m_driver;

	shared_ptr<SqlDriver> m_driver;  /* 是否正确？怎么使用最好？*/
	//SqlDriver *m_driver;

	//MYSQL_FIELD      *m_fields;
	//int              m_fields_num;
	//vector<string>   m_field_name;


};

#endif