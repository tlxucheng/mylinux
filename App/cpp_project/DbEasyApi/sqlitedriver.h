#pragma once

#ifndef SQLITEDRIVER_H
#define SQLITEDRIVER_H

#include "SqlDriver.h"
#include "sqlite3.h"

class SqliteDriver : public SqlDriver
{
public:
	SqliteDriver();
	~SqliteDriver();

	bool open(string& host, string& user, string& password, string& db, unsigned int port);
	sqlite3*  getSqliteHandle();

	//SqlResult *createResult() const;
private:
	sqlite3 *m_sqlite;
};

#endif