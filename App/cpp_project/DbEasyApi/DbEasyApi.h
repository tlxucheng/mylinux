#pragma once

#ifndef DBEASYAPI_H
#define DBEASYAPI_H

//#include <winsock.h>
#include "MySqlDriver.h"
#include "MySqlResult.h"
#include "Sqldatabase.h"

/*
 DbEasyApi 分离出5个类
 1. SqlDatabase 类，负责连接数据库        --- 已完成 11月15号
 2. SqlQueryModel 类，负责查询类
 3. SqlTableModel 类，负责table数据模型
 4. TableView类，负责表格模式显示数据
 5. ColumnView类，负责列模式显示数据

 question:
 1. 确认 shared_ptr<SqlDriver> m_sqldriver 是否能释放;
 */

class DbEasyApi
{
public:
	void setTable(string& tablename);  /* 将对应的表字段获取出来 */

	string& setFilter(string& filter);

	string& getTable();

	int select();
	int removeColumn(int column);
	int removeColumns(int column, int count);

	void showFields();
	void showResultColumn(MYSQL_RES *result); /* 将result转化成一个通用的Slqrecord类 */
	void showResultRow(MYSQL_RES *result);

public:
	Sqldatabase m_db;

private:
	string m_host;
	string m_user;
	string m_password;
	string m_dbname;
	int    m_port;
	string m_tablename;

	MySqlResult m_mysqlresult;
};

#endif