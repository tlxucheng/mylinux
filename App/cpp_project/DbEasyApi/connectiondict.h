#pragma once
#include <iostream>
#include <string>
#include <map>
#include "Sqldatabase.h"

class ConnectionDict
{
public:
	ConnectionDict();

	void insert(string& dbtype, Sqldatabase& db);
	Sqldatabase get(string& dbtype);

private:
	static map<string, Sqldatabase>* m_pInstance;
};