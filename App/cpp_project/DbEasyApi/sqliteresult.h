#pragma once

#ifndef SQLITERESULT_H
#define SQLITERESULT_H

#include "sqldatabase.h"

class SqliteResult : public SqlResult
{
public:
	SqliteResult();
	SqliteResult(Sqldatabase &db);

	bool reset(const string& sqlquery);
	AnyType data(int field);

    void show_fileds_type();
	void show_data(int index);
private:
	shared_ptr<SqlDriver> m_driver;  /* �Ƿ���ȷ����ôʹ����ã�*/

};


#endif