#include "stdafx.h"
#include "MySqlResult.h"
#include <iostream>
#include <iomanip>

using namespace std;

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

#if 0
int MySqlResult::GetResult(MYSQL *mysql, string& statement)
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
}
#endif

