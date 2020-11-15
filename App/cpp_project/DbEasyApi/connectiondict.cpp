#include "stdafx.h"
#include "connectiondict.h"

map<string, Sqldatabase>* ConnectionDict::m_pInstance = NULL;

ConnectionDict::ConnectionDict()
{
	if (NULL == m_pInstance)
	{
		m_pInstance = new map<string, Sqldatabase>;
	}
}

void ConnectionDict::insert(string& dbtype, Sqldatabase& db)
{
	m_pInstance->insert(pair<string, Sqldatabase>(dbtype, db));
}

Sqldatabase ConnectionDict::get(string& dbtype)
{
	map<string, Sqldatabase>::iterator it;

	it = m_pInstance->find(dbtype);
	if (it != m_pInstance->end())
	{
		cout << dbtype << " finded" << endl;
		return it->second;
	}
	else
	{
		cout << dbtype << " do not find" << endl;
		Sqldatabase db(dbtype);
		m_pInstance->insert(pair<string, Sqldatabase>(dbtype, db));

		return db;
	}
}