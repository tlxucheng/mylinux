// DbEasyApi.cpp : 定义控制台应用程序的入口点。
// 如何设置头文件和lib文件路径？
/* sqlite c api
 * https://blog.csdn.net/zgrjkflmkyc/article/details/45150951
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
#include "AnyType.h"
#include "sqltablemodel.h"

#include "sqlite3.h"

using namespace std;

DbEasyApi::DbEasyApi(string& dbtype)
{
	m_db = m_db.getDatabase(dbtype); 
}

void DbEasyApi::setTable(string& tablename)
{
	//m_db = Sqldatabase::getDatabase("MYSQL"); /* 语法错误 */
	//string dbtype = "MYSQL";
	//m_db = m_db.getDatabase(dbtype);  /* 应该写入构造函数 */

	m_tablename = tablename;

	m_mysqlresult.GetFields(m_db.m_sqldriver->getMysqlHandle(), tablename);

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

	result = m_mysqlresult.GetResult(m_db.m_sqldriver->getMysqlHandle(),statement);

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

void connect_mysql(string& dbname)
{
	string dbtype = "MYSQL";
	Sqldatabase db = Sqldatabase::addDatabase(dbtype);

	string host = "localhost";
	string user = "root";
	string password = "";
	
	db.setHost(host);
	db.setUser(user);
	db.setPassword(password);
	db.setDbname(dbname);

	db.open();

	return;
}

void anytype_test_function()
{
	AnyType test(100);

	int i = test.toInt();
	cout << "i: " << i << endl;

	AnyType test_str("my name is bob");
	string str = test_str.toString();
	cout << "str: " << str << endl;

	str.append("and age is 16.");
	cout << "str: " << str << endl;

	return;
}

void show_data_by_view()
{
	string  db_name = "test_db";

	connect_mysql(db_name);

	SqlTableModel *model = new SqlTableModel;
	model->setTable("yunzhi_nursing");   /* 为什么能编译通过 */
	model->select();
	model->show();

	/* 析构掉model */
}

int sqlite_print_record(void * params, int n_column, char **column_value, char **column_name)
{
	int i;

	for (i = 0; i<n_column; i++) {
		cout << setw(20) << column_value[i];
	}
	cout << endl;

	return 0;
}
void test_sqlite_api_static()
{
	sqlite3 *db = NULL;
	const char *select_sql = "select *from yunzhi_nursing";
	char *errmsg = NULL;

	if (sqlite3_open("D:/sqlite3/test_db", &db))
	{
		cout << "sqlite3_open failed!" << endl;
	}
	else
	{
		cout << "sqlite3_open suceess!" << endl;
	}

	if (sqlite3_exec(db, select_sql, sqlite_print_record, NULL, &errmsg))
	{
		cout << errmsg << endl;
	}

	return;
}

void test_sqlite_api_static2()
{
	sqlite3 *db = NULL;
	const char *select_sql = "select *from yunzhi_nursing";
	char *errmsg = NULL;
	char **dbresult; int j, nrow, ncolumn, index;
	int ret = 0;

	if (sqlite3_open("D:/sqlite3/test_db", &db))
	{
		cout << "sqlite3_open failed!" << endl;
	}
	else
	{
		cout << "sqlite3_open suceess!" << endl;
	}

	int i = 0;
	ret = sqlite3_get_table(db, select_sql, &dbresult, &nrow, &ncolumn, &errmsg);
	if (ret == SQLITE_OK) {
		cout << "query " << nrow << " records. " << endl;
		printf("query %i records.\n", nrow);
		index = ncolumn;
		for (i = 0; i<nrow; i++) {
			cout << setw(2) << i;
			for (j = 0; j < ncolumn; j++) {
				if (NULL != dbresult[index])         /* https://bbs.csdn.net/topics/390187094 */
				{
				    cout << " " << dbresult[index]; 
			    }
												   /* 尝试 https://blog.csdn.net/jqsad/article/details/51782088 中的方法2 */
				//printf(" %s", dbresult[index]);
				index++;
			}
			cout << endl;
		}
	}
	sqlite3_free_table(dbresult);

	sqlite3_close(db);

	return;
}

int main()
{
#if 0
	string dbname = "test_db";
	string tablename = "yunzhi_nursing"; // yunzhi_teacher 表中有中文，会出现乱码
	connect_mysql(dbname);

	string dbtype = "MYSQL";
	DbEasyApi test(dbtype);

	test.setTable(tablename); /* m_mysql为空值 */

	test.showFields();    /* 调用设置表名函数后就会查询出字段信息 */
	//test.removeColumn(0); /* 跳跃删除 */
	//test.removeColumn(1);
	//test.removeColumn(2);
	test.removeColumns(0,4);
	test.showFields();
	//test.open();
	test.select();
#endif

	/* test Sqldatabase */
#if 0
	string dbtype = "MYSQL";
	Sqldatabase db;
    db.addDatabase(dbtype);
	db.getDatabase(dbtype);

    dbtype = "SQlite";  
	db.getDatabase(dbtype);
	db.getDatabase(dbtype);
#endif

	//anytype_test_function();

	//system("pause");

	/* show_data_by_view function */
	//show_data_by_view();

	//test_sqlite_api_static();

	test_sqlite_api_static2();
	
	return 0;
}

