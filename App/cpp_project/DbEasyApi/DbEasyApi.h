#pragma once

#ifndef DBEASYAPI_H
#define DBEASYAPI_H

//#include <winsock.h>
#include "MySqlDriver.h"
#include "MySqlResult.h"

class DbEasyApi
{
public:
	void setHost(string& host);
	void setUser(string& user);
	void setPassword(string& password);
	void setDbname(string& dbname);
	void setPort(int port);
	void setTable(string& tablename);  /* 将对应的表字段获取出来 */

	string& setFilter(string& filter);

	string& getTable();

	int open();
	int select();
	int removeColumn(int column);

	void showFields();
private:
	string m_host;
	string m_user;
	string m_password;
	string m_dbname;
	int    m_port;
	string m_tablename;

	MysqlDriver m_mysqldriver;
	MySqlResult m_mysqlresult;
};

#endif