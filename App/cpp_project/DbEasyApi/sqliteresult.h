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
	shared_ptr<SqlDriver> m_driver;  /* �Ƿ���ȷ����ôʹ����ã�*/

};


#endif