#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include "sqliteresult.h"
#include "sqlitedriver.h"

using namespace std;

SqliteResult::SqliteResult()
{

}

SqliteResult::SqliteResult(Sqldatabase &db)
{
	m_driver = db.m_sqldriver;
}

/* �����������������close�ӿ� */

bool SqliteResult::reset(const string& query)
{
	SqliteDriver    *m_driver_ptr = reinterpret_cast<SqliteDriver *>(m_driver.get());
	int             ret           = 0;
	char            **dbresult    = NULL;
	char            *errmsg       = NULL;
	int             nrow          = 0;
	int             ncolumn       = 0;  
	int             i             = 0;
	int             j             = 0;
	int             index         = 0;

	cout << "query: " << query << endl;

	ret = sqlite3_get_table(m_driver_ptr->m_sqlite, query.c_str(), &dbresult, &nrow, &ncolumn, &errmsg);
	if (ret == SQLITE_OK)
	{
		index = ncolumn;
		for (i = 0; i<nrow; i++) {
			cout << setw(2) << i;
			for (j = 0; j < ncolumn; j++) {
				if (NULL != dbresult[index])       
				{
					cout << " " << dbresult[index];
				}
				index++;
			}
			cout << endl;
		}
	}

	return FALSE;
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