#pragma once

#ifndef SQLQUERY_H
#define SQLQUERY_H

#include <iostream>
#include <string>
#include "sqldatabase.h"

using namespace std;

class SqlQuery
{
public:
	//explicit SqlQuery(SqlResult *r);
	//explicit SqlQuery();
	SqlQuery();
	SqlQuery(const string& query, Sqldatabase &db);
	//Init(const string& query, Sqldatabase &db);
private:

	SqlResult *sqlResult;
};

#endif 

