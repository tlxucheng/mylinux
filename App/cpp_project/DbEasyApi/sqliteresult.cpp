#include "stdafx.h"
#include "sqliteresult.h"

using namespace std;

SqliteResult::SqliteResult()
{

}

SqliteResult::SqliteResult(Sqldatabase &db)
{
	m_driver = db.m_sqldriver;
}

bool SqliteResult::reset(const string& query)
{
	return TRUE;
}

AnyType SqliteResult::data(int filed)
{
	return AnyType();  /* ����һ��ʲô���Ķ���ȽϺ� */
}


void SqliteResult::show_fileds_type()
{
	return;
}

void SqliteResult::show_data(int index)
{

	return;
}