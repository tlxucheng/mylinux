#include "stdafx.h"
#include "sqlquery.h"

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
	/* 申请 sqlResult 指针空间, db参数先不用 */

	this->sqlResult->reset(query);
}
