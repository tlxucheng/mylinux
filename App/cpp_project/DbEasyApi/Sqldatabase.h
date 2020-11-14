#pragma once
#include <iostream>
#include <string>
#include <map>
#include "sqlDriver.h"

using namespace std;

class Sqldatabase
{
public:
	Sqldatabase();
	~Sqldatabase();

	Sqldatabase addDatabase(string& type);

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

	SqlDriver *m_sqldriver;
	static Sqldatabase *m_pInstance;
	map<string, Sqldatabase*> m_conn;
};