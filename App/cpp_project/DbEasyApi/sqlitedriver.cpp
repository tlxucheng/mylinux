#include "stdafx.h"
#include "SqliteDriver.h"

using namespace std;

SqliteDriver::SqliteDriver()
{
	m_sqlite = NULL;
}

SqliteDriver::~SqliteDriver()
{
	if (NULL != m_sqlite)
	{
		sqlite3_close(m_sqlite);
	}

	cout << "close sqlite connect" << endl;
}

/* ��һЩʲô�¼��ȽϺ� */
bool SqliteDriver::init()
{
	return true;
}

bool SqliteDriver::open(string& host, string& user, string& password, string& db, unsigned int port)
{
	if (sqlite3_open(db.c_str(), &m_sqlite))
	{
		cout << "sqlite3_open failed!" << endl;

		return false;
	}

	return true;
}

sqlite3* SqliteDriver::getSqliteHandle()
{
	return m_sqlite;
}

/* ��δʵ�� */
SqlResult* SqliteDriver::createResult() const
{
	return NULL;  
}