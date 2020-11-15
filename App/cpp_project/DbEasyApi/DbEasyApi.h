#pragma once

#ifndef DBEASYAPI_H
#define DBEASYAPI_H

//#include <winsock.h>
#include "MySqlDriver.h"
#include "MySqlResult.h"
#include "Sqldatabase.h"

/*
 DbEasyApi �����5����
 1. SqlDatabase �࣬�����������ݿ�        --- ����� 11��15��
 2. SqlQueryModel �࣬�����ѯ��
 3. SqlTableModel �࣬����table����ģ��
 4. TableView�࣬������ģʽ��ʾ����
 5. ColumnView�࣬������ģʽ��ʾ����
 6. Connectiondict��ʹ����ģ��ʵ��

 question:
 1. ȷ�� shared_ptr<SqlDriver> m_sqldriver �Ƿ����ͷ�;
 */

class DbEasyApi
{
public:
	void setTable(string& tablename);  /* ����Ӧ�ı��ֶλ�ȡ���� */

	string& setFilter(string& filter);

	string& getTable();

	int select();
	int removeColumn(int column);
	int removeColumns(int column, int count);

	void showFields();
	void showResultColumn(MYSQL_RES *result); /* ��resultת����һ��ͨ�õ�Slqrecord�� */
	void showResultRow(MYSQL_RES *result);

public:
	Sqldatabase m_db;

private:
	string m_host;
	string m_user;
	string m_password;
	string m_dbname;
	int    m_port;
	string m_tablename;

	MySqlResult m_mysqlresult;
};

#endif