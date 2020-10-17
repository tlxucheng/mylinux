#pragma once

#ifndef DBEASYAPI_H
#define DBEASYAPI_H

//#include <winsock.h>
#include "MySqlDriver.h"

class DbEasyApi
{
public:
	void setHost(string& host);
	void setUser(string& user);
	void setPassword(string& password);
	void setDbname(string& dbname);
	void setPort(int port);

	int open();
private:
	string m_host;
	string m_user;
	string m_password;
	string m_dbname;
	int    m_port;

	MysqlDriver m_mysqldriver;
};

#endif