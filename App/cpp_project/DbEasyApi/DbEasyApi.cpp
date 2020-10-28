// DbEasyApi.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
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

int DbEasyApi::select()
{
	string action = "select";
	string blank_space = " ";
	string condition = "*from";
	//string statement = "select *from yunzhi_nursing";

	string statement = action + blank_space + condition + blank_space + getTable();

	m_mysqlresult.GetResult(m_mysqldriver.getMysqlHandle(),statement);

	return 0;
}

int main()
{
	DbEasyApi test;
	string host = "localhost";
	string user = "root";
	string password = "";
	string dbname = "test_db";
	string tablename = "yunzhi_teacher";

	test.setHost(host);  //不用使用 test.setHost("localhost")
	test.setUser(user);
	test.setPassword(password);
	test.setDbname(dbname);
	test.setPort(3306);
	test.setTable(tablename);

	test.open();
	test.select();

	//system("pause");

    return 0;
}

