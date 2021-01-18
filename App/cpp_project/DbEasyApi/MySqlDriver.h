#pragma once

#ifndef MYSQLDRIVER_H
#define MYSQLDRIVER_H

#include "SqlDriver.h"
#include "SqlResult.h"
#include "Sqldatabase.h"

class MysqlDriver : public SqlDriver
{
public:
	MysqlDriver();
	~MysqlDriver();

	bool    init();
	bool    open(string& host, string& user, string& password, string& db, unsigned int port);
	//MYSQL*  getMysqlHandle();

    SqlResult *createResult() const;
	SqlResult *createResult(Sqldatabase &db) const;
public:
	MYSQL   *m_mysql;
};

#endif