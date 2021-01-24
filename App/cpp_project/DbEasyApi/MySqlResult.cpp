#include "stdafx.h"
#include "MySqlResult.h"
#include "AnyType.h"
#include <iostream>
#include <iomanip>

using namespace std;

MySqlResult::MySqlResult()
{

}

MySqlResult::MySqlResult(Sqldatabase &db)
{
	m_driver = db.m_sqldriver;
}

vector<MyFields>& MySqlResult::getField()
{
	return m_fields;
};

void MySqlResult::setField(vector<MyFields>& fields)
{
	m_fields = fields;

	return;
};

//mysql_free_result(res); 
int MySqlResult::GetFields(MYSQL *mysql, string& tablename)
{
	MYSQL_FIELD *field = NULL;

	MYSQL_RES *r = mysql_list_fields(mysql, tablename.c_str(), 0);
	if (!r)
	{
		cout << "mysql_list_fields failed!" << endl;
		return -1;
	}
	else
	{
		cout << "mysql_list_fields success!" << endl;
	}

	while (field = mysql_fetch_field(r))
	{
		MyFields field_info;
		field_info.name = field->name;
		field_info.type = field->type;
		m_fields.push_back(field_info);
	}
	
	mysql_free_result(r);

	return 0;
}

MYSQL_RES* MySqlResult::GetResult(MYSQL *mysql, string& statement)
{
	if (mysql_real_query(mysql, statement.c_str(), static_cast<unsigned long>(statement.length())))
	{
		cout << "myslq query failed!" << endl;
	}
	else
	{
		cout << "myslq query success!" << endl;

	}

	cout << setiosflags(ios::fixed) << setprecision(6) << setiosflags(ios::left);

	m_result = mysql_store_result(mysql);

	return m_result;
#if 0
	m_fields = mysql_fetch_fields(m_result);
	m_fields_num = mysql_num_fields(m_result);

	int i = 0;
	for (i = 0; i < m_fields_num; i++)
	{
		m_field_name.push_back(m_fields[i].name);
		cout << setw(20) << m_fields[i].name;
	}
	cout << endl;

	MYSQL_ROW   rows;
	int num_row = static_cast<int>(mysql_num_rows(m_result));
	for(i = 0; i < num_row; i++)
	{
		rows = mysql_fetch_row(m_result);
		if (NULL != rows)
		{
			int j = 0;
			for (j = 0; j < m_fields_num; j++)
			{
				cout << setw(20) << rows[j];
			}
			cout << endl;
		}
	}
	cout << endl;

	return 0;
#endif
}

static int DecodeMYSQLType(int mysqltype, int flags)
{
	int type = 0;

	switch (mysqltype)
	{
		case FIELD_TYPE_TINY:
		case FIELD_TYPE_SHORT:
		case FIELD_TYPE_LONG:
		case FIELD_TYPE_INT24:
			type = AnyType::Int;
			break;
		case FIELD_TYPE_LONGLONG:
			type = AnyType::Long;
			break;
		case FIELD_TYPE_ENUM:
		case FIELD_TYPE_SET:
		case FIELD_TYPE_DATE:                   /* 先认为是String */ 
		case FIELD_TYPE_TIME:                   /* 先认为是String */ 
		case FIELD_TYPE_STRING:
		case FIELD_TYPE_VAR_STRING:
			type = AnyType::String;
			break;
		default:
			break;
	}

	return type;
}

bool MySqlResult::reset(const string& query)
{ 
	MysqlDriver *m_driver_ptr = reinterpret_cast<MysqlDriver *>(m_driver.get());

	cout << "query: " << query << endl;

	if (mysql_real_query(m_driver_ptr->m_mysql, query.c_str(), query.length()))
	{
		return false;
	}
	m_result = mysql_store_result(m_driver_ptr->m_mysql);
	if (NULL == m_result)
	{
		return false;
	}
	int num_fileds = mysql_field_count(m_driver_ptr->m_mysql);
	for (int i = 0; i < num_fileds; i++)
	{
		MYSQL_FIELD *field = mysql_fetch_field_direct(m_result, i);  //mysql_fetch_field_direct与mysql_fetch_field的区别？

		MyFields field_info;
		field_info.name = field->name;
		field_info.type = DecodeMYSQLType(field->type, field->flags);
		m_fields.push_back(field_info);
	}

	return true;
}

AnyType MySqlResult::data(int filed)
{
	return AnyType();  /* 创建一个什么样的对象比较好 */
}

void MySqlResult::show_fileds()
{
	size_t filed_vector_size = m_fields.size();

	for (int i = 0; i < filed_vector_size; i++)
	{
		cout << i << " type: " << m_fields[i].type << endl;
	}

	return;
}

void MySqlResult::show_data(int index)
{
    mysql_data_seek(m_result, index);
    m_row = mysql_fetch_row(m_result);

	if (NULL != m_row)
	{
		int i = 0;
		size_t filed_vector_size = m_fields.size();
		for (i = 0; i < filed_vector_size; i++)
		{
			cout << setw(20) << m_row[i];
		}
		cout << endl;
	}

    return;
}

void MySqlResult::show_data()
{
	return;
}