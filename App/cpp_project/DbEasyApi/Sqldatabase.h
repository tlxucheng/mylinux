#pragma once
#include <iostream>
#include <string>
#include <map>
#include <memory>
#include "sqlDriver.h"
#include "MysqlDriver.h"

using namespace std;

class Sqldatabase
{
public:
	Sqldatabase::Sqldatabase();
	Sqldatabase(string& dbtype);
	~Sqldatabase();

	void addDatabase(string& dbtype);
	Sqldatabase getDatabase(string& dbtype);

	void setHost(string& host);
	void setUser(string& user);
	void setPassword(string& password);
	void setDbname(string& dbname);
	void setPort(int port);

private:
	string m_host;
	string m_user;
	string m_password;
	string m_dbname;
	int    m_port;

	shared_ptr<SqlDriver> m_sqldriver;
	//MysqlDriver *m_sqldriver;
};