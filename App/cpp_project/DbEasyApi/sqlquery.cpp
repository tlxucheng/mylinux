#include "stdafx.h"
#include "sqlquery.h"

SqlQuery::SqlQuery()
{

}

/*
void Init(const string& query, Sqldatabase &db)
{
	SqlQuery *q = SqlQuery(db.m_sqldriver->createResult());
}

SqlQuery::SqlQuery()
{

}

SqlQuery::SqlQuery(SqlResult *r)
{
	if (NULL == r)
	{
		new SqlQuery;
	}
}
*/

SqlQuery::SqlQuery(const string& query, Sqldatabase &db)
{
	/* ���� sqlResult ָ��ռ�, db�����Ȳ��� */

	this->sqlResult->reset(query);
}
