#include "stdafx.h"
#include "sqldatabase.h"
#include "connectiondict.h"
#include "MysqlDriver.h"

Sqldatabase::Sqldatabase()
{
	m_sqldriver = NULL;
}

Sqldatabase::Sqldatabase(string& dbtype)
{
	if ("MYSQL" == dbtype)
	{
		m_sqldriver = make_shared<MysqlDriver>();
	}
	else
	{
		m_sqldriver = NULL;
	}
}

Sqldatabase::~Sqldatabase()
{
	if (NULL != m_sqldriver)
	{
		//delete m_sqldriver; /* crash�������麯���ĳ��麯�������в�crash�����ǵ��Ի�crash, �ȸĳ�����ָ��ʵ�� */
	}
}

void Sqldatabase::addDatabase(string& dbtype)
{
	ConnectionDict dbDict;
	Sqldatabase db(dbtype);

	dbDict.insert(dbtype, db);

	return;
}

Sqldatabase Sqldatabase::getDatabase(string& dbtype)
{
	ConnectionDict dbDict;

	Sqldatabase db = dbDict.get(dbtype);

	return db;
}

void Sqldatabase::setHost(string& host)
{
	m_host = host;
}

void Sqldatabase::setUser(string& user)
{
	m_user = user;
}

void Sqldatabase::setPassword(string& password)
{
	m_password = password;
}

void Sqldatabase::setDbname(string& dbname)
{
	m_dbname = dbname;
}

void Sqldatabase::setPort(int port)
{
	m_port = port;
}
