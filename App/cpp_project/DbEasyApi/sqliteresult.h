#pragma once

#ifndef SQLITERESULT_H
#define SQLITERESULT_H

#include "sqldatabase.h"

class SqliteResult : public SqlResult
{
public:
	SqliteResult();
	SqliteResult(Sqldatabase &db);

private:
	shared_ptr<SqlDriver> m_driver;  /* 是否正确？怎么使用最好？*/

};


#endif