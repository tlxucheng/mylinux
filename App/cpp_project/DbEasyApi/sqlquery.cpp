#include "stdafx.h"
#include "sqlquery.h"
#include "MySqlResult.h"

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
	/* 申请 sqlResult 指针空间, db参数先不用 */
	if (NULL == sqlResult)
	{
		//sqlResult = new MySqlResult(db);  /* 如何使用this指针 */

		sqlResult = db.m_sqldriver->createResult(db);
	}

	//this->sqlResult->reset(query);
	sqlResult->reset(query);
}

SqlResult *SqlQuery::getSqlResult()
{
	return sqlResult;
}
