#pragma once
#include <iostream>
#include <string>
#include <map>
#include "Sqldatabase.h"

template<typename T>
class ConnectionDict
{
public:
	ConnectionDict()
	{
		if (NULL == m_pInstance)
		{
			m_pInstance = new map<string, T>;
		}
	}

	void insert(string& dbtype, T& db)
	{
		m_pInstance->insert(pair<string, T>(dbtype, db));
	}

	T get(string& dbtype)
	{
		map<string, T>::iterator it;

		it = m_pInstance->find(dbtype);
		if (it != m_pInstance->end())
		{
			cout << dbtype << " finded" << endl;
			return it->second;
		}
		else
		{
			cout << dbtype << " do not find" << endl;
			T db(dbtype);
			m_pInstance->insert(pair<string, T>(dbtype, db));

			return db;
		}
	}

private:
	static map<string, T>* m_pInstance;
};

template<typename T>
map<string, T>* ConnectionDict<T>::m_pInstance = NULL;
