#include "stdafx.h"
#include "sqldatabase.h"

Sqldatabase* Sqldatabase::m_pInstance = NULL;

Sqldatabase::Sqldatabase()
{
	m_pInstance = new Sqldatabase();
}

Sqldatabase::~Sqldatabase()
{
	if (NULL != m_sqldriver)
	{
		delete m_sqldriver;
	}
		
    if(NULL != m_pInstance)
	{
		delete m_pInstance;
	}
}

Sqldatabase Sqldatabase::addDatabase(string& dbtype)
{
	Sqldatabase db;
	m_conn.insert(pair<string, Sqldatabase*>(dbtype, m_pInstance));

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
