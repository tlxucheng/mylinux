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
 3. SqlTableModel �࣬������SqlQueryModel������table����ģ��
 4. AbstractItemView �࣬��Ϊ������ʾ��ĸ���
 4. TableView�࣬������AbstractItemView��������ģʽ��ʾ����
 5. ColumnView�࣬������AbstractItemView��������ģʽ��ʾ����
 6. Connectiondict ��ʹ����ģ��ʵ��       --- ����� 11��15��
 7. Connectiondict ��Ҫ����������

 8. ���� ����ɾ���Ľӿ�
 9. socketģ�ͽӿڿ�����֧�ֶ��̡߳�selectģ�͡�epollģ�ͣ�Linux�£�֧��UDP/TCL/TLS/SCTP
 10. ���Բ�ѯ��ʷ�����¼
 11. ֧�ֶ���Э��ͻ��˲��Թ���
 12. ����Windows��Linux

 question:
 1. ȷ�� shared_ptr<SqlDriver> m_sqldriver �Ƿ����ͷ�;
 2. ���mysql serverû������crash
 */

class DbEasyApi
{
public:
	explicit DbEasyApi(string& dbtype);

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
	string m_tablename;

	MySqlResult m_mysqlresult;
};

#endif