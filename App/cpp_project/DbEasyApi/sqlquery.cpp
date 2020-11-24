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
	/* ÉêÇë sqlResult Ö¸Õë¿Õ¼ä */

	this->sqlResult->reset(query);
}
