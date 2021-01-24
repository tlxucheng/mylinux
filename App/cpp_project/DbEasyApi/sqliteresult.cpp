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

static int DecodeSQLITEType(int sqlite_type)
{
	int type = 0;

	switch (sqlite_type)
	{
	case SQLITE_INTEGER:
		type = AnyType::Int;
		break;
	case SQLITE_TEXT:
		type = AnyType::String;
		break;
	default:
		break;
	}

	return type;
}

string DecodeFiledType(int type)
{
	string str = "SQLITE_INTEGER";

	switch (type)
	{
	case AnyType::Int:
		return str;
	case AnyType::String:
		str = "SQLITE_TEXT";
		return str;
	default:
		break;
	}

	return str;
}



/* ���ʹ��pragma table_info('yunzhi_nursing')��ȡ�ֶ���Ϣ
 * ʹ������ķ���������ֶ��ǿյģ�����ȡ��������
 */
int SqliteResult::get_fileds_type(const string& query)
{
	sqlite3_stmt      *stmt            = NULL;
	SqliteDriver      *m_driver_ptr    = reinterpret_cast<SqliteDriver *>(m_driver.get());
	MyFields          field_info;

	sqlite3_prepare(m_driver_ptr->m_sqlite, query.c_str(), -1, &stmt, 0);
	while (stmt)
	{
		while (SQLITE_ROW == sqlite3_step(stmt))
		{
			int nCount = sqlite3_column_count(stmt);
			for (int i = 0; i < nCount; i++)
			{
				//int nValue = sqlite3_column_int(stmt, 0);
				int nType = sqlite3_column_type(stmt, i);

				field_info.type = DecodeSQLITEType(nType);
				m_fields.push_back(field_info);
			}
			break;
		}

		sqlite3_finalize(stmt);
		stmt = NULL;
	}

	return 0;
}

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

	cout << setiosflags(ios::fixed) << setprecision(6) << setiosflags(ios::left);

	get_fileds_type(query);

	ret = sqlite3_get_table(m_driver_ptr->m_sqlite, query.c_str(), &dbresult, &nrow, &ncolumn, &errmsg);
	if (ret == SQLITE_OK)
	{
		for (i = 0; i < ncolumn; i++)
		{
			cout << setw(20) << dbresult[i];
			m_fields[i].name = dbresult[i];
		}
		cout << endl;

		m_fields_count = ncolumn;

		index = ncolumn;
		for (i = 0; i<nrow; i++) {
			//cout << setw(2) << i;
			for (j = 0; j < ncolumn; j++) {
				if (NULL != dbresult[index])       
				{
					cout << setw(20) << dbresult[index];
					m_values.push_back(dbresult[index]);
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


void SqliteResult::show_fileds()
{
	size_t filed_vector_size = m_fields.size();

	for (int i = 0; i < filed_vector_size; i++)
	{
		cout << i << " type: " << DecodeFiledType(m_fields[i].type) << "  name: " << m_fields[i].name << endl;
	}

	return;
}

void SqliteResult::show_data(int index)
{

	return;
}

void SqliteResult::show_data()
{
	size_t filed_vector_size = m_values.size();
	for (int i = 0; i < filed_vector_size; i++)
	{
		if (0 == i % m_fields_count)
		{
			cout << endl;
		}
		cout << m_values[i] << "  ";
	}

	cout << endl;

	return;
}