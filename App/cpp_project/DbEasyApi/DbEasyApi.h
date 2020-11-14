#pragma once

#ifndef DBEASYAPI_H
#define DBEASYAPI_H

//#include <winsock.h>
#include "MySqlDriver.h"
#include "MySqlResult.h"

/*
 DbEasyApi �����5����
 1. SqlDatabase �࣬�����������ݿ�
 2. SqlQueryModel �࣬�����ѯ��
 3. SqlTableModel �࣬����table����ģ��
 4. TableView�࣬������ģʽ��ʾ����
 5. ColumnView�࣬������ģʽ��ʾ����
 */

class DbEasyApi
{
public:
	void setHost(string& host);
	void setUser(string& user);
	void setPassword(string& password);
	void setDbname(string& dbname);
	void setPort(int port);
	void setTable(string& tablename);  /* ����Ӧ�ı��ֶλ�ȡ���� */

	string& setFilter(string& filter);

	string& getTable();

	int open();
	int select();
	int removeColumn(int column);
	int removeColumns(int column, int count);

	void showFields();
	void showResultColumn(MYSQL_RES *result); /* ��resultת����һ��ͨ�õ�Slqrecord�� */
	void showResultRow(MYSQL_RES *result);
private:
	string m_host;
	string m_user;
	string m_password;
	string m_dbname;
	int    m_port;
	string m_tablename;

	MysqlDriver m_mysqldriver;
	MySqlResult m_mysqlresult;
};

#endif