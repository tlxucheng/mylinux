#include "stdafx.h"
#include <iostream>
#include "MysqlDriver.h"
#include "MysqlResult.h"

using namespace std;

MysqlDriver::MysqlDriver()
{
	m_mysql = NULL;
}

MysqlDriver::~MysqlDriver()
{
	if (NULL != m_mysql)
	{
		mysql_close(m_mysql);
	}

	cout << "close mysql connect" << endl;
}

bool MysqlDriver::init()
{
    m_mysql = mysql_init(NULL);
	//m_mysql = mysql_init(m_mysql);  /* crashԭ����ʲô */
	if (NULL == m_mysql)
	{
		return false;
	}

	return true;
}

bool MysqlDriver::open(string& host, string& user, string& password, string& db, unsigned int port)
{
	if (NULL == mysql_real_connect(m_mysql, host.c_str(), user.c_str(), password.c_str(), db.c_str(), port, NULL, 0))
	{
		return false;
	}

	return true;
}

MYSQL* MysqlDriver::getMysqlHandle()
{
	return m_mysql;
}

SqlResult* MysqlDriver::createResult() const
{
	return new MySqlResult;  /* ��return new MySqlResult(this)�����𣬺�ʱɾ�� */
}