// DbEasyApi.cpp : 定义控制台应用程序的入口点。
//

/*
typedef enum enum_field_types {
	MYSQL_TYPE_DECIMAL, MYSQL_TYPE_TINY,
	MYSQL_TYPE_SHORT, MYSQL_TYPE_LONG,
	MYSQL_TYPE_FLOAT, MYSQL_TYPE_DOUBLE,
	MYSQL_TYPE_NULL, MYSQL_TYPE_TIMESTAMP,
	MYSQL_TYPE_LONGLONG, MYSQL_TYPE_INT24,
	MYSQL_TYPE_DATE, MYSQL_TYPE_TIME,
	MYSQL_TYPE_DATETIME, MYSQL_TYPE_YEAR,
	MYSQL_TYPE_NEWDATE, MYSQL_TYPE_VARCHAR,
	MYSQL_TYPE_BIT,
	MYSQL_TYPE_TIMESTAMP2,
	MYSQL_TYPE_DATETIME2,
	MYSQL_TYPE_TIME2,
	MYSQL_TYPE_JSON = 245,
	MYSQL_TYPE_NEWDECIMAL = 246,
	MYSQL_TYPE_ENUM = 247,
	MYSQL_TYPE_SET = 248,
	MYSQL_TYPE_TINY_BLOB = 249,
	MYSQL_TYPE_MEDIUM_BLOB = 250,
	MYSQL_TYPE_LONG_BLOB = 251,
	MYSQL_TYPE_BLOB = 252,
	MYSQL_TYPE_VAR_STRING = 253,
	MYSQL_TYPE_STRING = 254,
	MYSQL_TYPE_GEOMETRY = 255
} enum_field_types;
*/

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include "Sqldatabase.h"
#include "DbEasyApi.h"

using namespace std;

void DbEasyApi::setHost(string& host)
{
	m_host = host;
}

void DbEasyApi::setUser(string& user)
{
	m_user = user;
}

void DbEasyApi::setPassword(string& password)
{
	m_password = password;
}

void DbEasyApi::setDbname(string& dbname)
{
	m_dbname = dbname;
}

void DbEasyApi::setPort(int port)
{
	m_port = port;
}

void DbEasyApi::setTable(string& tablename)
{
	m_tablename = tablename;

	/* 获取对应表的表字段 */
	DbEasyApi::open();

	m_mysqlresult.GetFields(m_mysqldriver.getMysqlHandle(), tablename);

	return;
}

int DbEasyApi::removeColumn(int column)
{
	vector<MyFields>fields;
	vector<MyFields>::iterator it;

	fields = m_mysqlresult.getField();
	it = fields.begin() + column;
	fields.erase(it);

	m_mysqlresult.setField(fields);

	return 0;
}

int DbEasyApi::removeColumns(int column, int count)
{
	int i = 0;

	for (i = 0; i < count; i++)
	{
		removeColumn(column);
	}

	return 0;
}

void DbEasyApi::showFields()
{
	vector<MyFields>::iterator it;
	vector<MyFields>fields;

	cout << setiosflags(ios::fixed) << setprecision(6) << setiosflags(ios::left);

	fields = m_mysqlresult.getField();
	for (it = fields.begin(); it != fields.end(); it++)
	{
		cout << setw(20) << (*it).name << "    " << setw(20) << (*it).type << endl;
	}

	cout << endl;

	return;
}

string& DbEasyApi::getTable()
{
	return m_tablename;
}

int DbEasyApi::open()
{
	if (m_mysqldriver.init())
	{
		if (m_mysqldriver.open(m_host, m_user, m_password, m_dbname, m_port))
		{
			cout << "db open success!" << endl;
			return true;
		}
	}

	cout << "db open failed!" << endl;

	return false;
}

string& DbEasyApi::setFilter(string& filter)
{
	filter.insert(0, " where ");

	return filter;
}

int DbEasyApi::select()
{
    MYSQL_RES *result;
	MYSQL_RES result_row;

	string action = "select ";
	string condition;
	string filter = "project_date = '2020-10-07'";
	
	vector<MyFields>fields;
	vector<MyFields>::iterator it;
	fields = m_mysqlresult.getField();
	for (it = fields.begin(); it != fields.end(); it++)
	{
		condition.append((*it).name).append(", ");
	}
	condition.erase(condition.end() - 2);
	condition.append("from ");

	string statement;
	statement.append(action).append(condition).append(getTable()).append(setFilter(filter));

	cout << statement << endl;

	result = m_mysqlresult.GetResult(m_mysqldriver.getMysqlHandle(),statement);

	memcpy(&result_row, result, sizeof(result_row));
	showResultColumn(result);
	showResultRow(&result_row);

	return 0;
}

void DbEasyApi::showResultColumn(MYSQL_RES *result)
{
	MYSQL_FIELD *res_fields = mysql_fetch_fields(result);
	int res_fields_num = mysql_num_fields(result);
	vector<string>  res_field_name;

	int i = 0;
	for (i = 0; i < res_fields_num; i++)
	{
		res_field_name.push_back(res_fields[i].name);
		cout << setw(20) << res_fields[i].name;
	}
	cout << endl;

	MYSQL_ROW   rows;
	int num_row = static_cast<int>(mysql_num_rows(result));
	for (i = 0; i < num_row; i++)
	{
		rows = mysql_fetch_row(result);
		if (NULL != rows)
		{
			int j = 0;
			for (j = 0; j < res_fields_num; j++)
			{
				cout << setw(20) << rows[j];
			}
			cout << endl;
		}
	}
	cout << endl;

	return;
}

void DbEasyApi::showResultRow(MYSQL_RES *result)
{
	MYSQL_FIELD *res_fields = mysql_fetch_fields(result);
	int res_fields_num = mysql_num_fields(result);
	vector<string>  res_field_name;

	int i = 0;
	for (i = 0; i < res_fields_num; i++)
	{
		res_field_name.push_back(res_fields[i].name);
	}

	MYSQL_ROW   rows;
	int num_row = static_cast<int>(mysql_num_rows(result));
	for (i = 0; i < num_row; i++)
	{
		rows = mysql_fetch_row(result);
		if (NULL != rows)
		{
			cout << "***************************" << " " << i + 1 << ". row ***************************" << endl;
			int j = 0;
			for (j = 0; j < res_fields_num; j++)
			{
				cout << setw(20) << res_fields[j].name;
				cout << ": ";
				cout << setw(20) << rows[j];
				cout << endl;
			}
		}
	}
	cout << endl;

	return;
}

int main()
{
	DbEasyApi test;
	string host = "localhost";
	string user = "root";
	string password = "";
	string dbname = "test_db";
	string tablename = "yunzhi_nursing"; // yunzhi_teacher 表中有中文，会出现乱码

	test.setHost(host);  //不用使用 test.setHost("localhost")
	test.setUser(user);
	test.setPassword(password);
	test.setDbname(dbname);
	test.setPort(3306);
	test.setTable(tablename);

	test.showFields();    /* 调用设置表名函数后就会查询出字段信息 */
	//test.removeColumn(0); /* 跳跃删除 */
	//test.removeColumn(1);
	//test.removeColumn(2);
	test.removeColumns(0,4);
	test.showFields();
	//test.open();
	test.select();

	/* test Sqldatabase */
	string dbtype = "MYSQL";
	Sqldatabase db;
    db.addDatabase(dbtype);
	//db.getDatabase(dbtype); /* crash */

	//string dbtype2 = "SQlite";  /* 赋值能直接覆盖掉先前的赋值吗？ */
	//db.getDatabase(dbtype2);

	//system("pause");

    return 0;
}

