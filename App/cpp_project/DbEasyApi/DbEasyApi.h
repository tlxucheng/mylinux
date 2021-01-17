#pragma once

#ifndef DBEASYAPI_H
#define DBEASYAPI_H

//#include <winsock.h>
#include "MySqlDriver.h"
#include "MySqlResult.h"
#include "Sqldatabase.h"

/*
 DbEasyApi 分离出5个类
 1. SqlDatabase 类，负责连接数据库        --- 已完成 11月15号
 2. SqlQueryModel 类，负责查询类
 3. SqlTableModel 类，父类是SqlQueryModel，负责table数据模型
 4. AbstractItemView 类，作为所有显示类的父类
 4. TableView类，父类是AbstractItemView，负责表格模式显示数据
 5. ColumnView类，父类是AbstractItemView，负责列模式显示数据
 6. Connectiondict 类使用类模板实现       --- 已完成 11月15号
 7. Connectiondict 需要增加锁控制

 8. 增加 增、删、改接口
 9. socket模型接口开发，支持多线程、select模型、epoll模型（Linux下）支持UDP/TCL/TLS/SCTP
 10. 可以查询历史聊天记录
 11. 支持多种协议客户端测试工具
 12. 兼容Windows和Linux

 question:
 1. 确认 shared_ptr<SqlDriver> m_sqldriver 是否能释放;
 2. 如果mysql server没启动会crash
 3. 去除 getMysqlHandle 函数后，mysql接口功能未测试
 4. mysql句柄获取修改为一个宏，m_mysql修改为友元变量？
 */

class DbEasyApi
{
public:
	explicit DbEasyApi(string& dbtype);

	void setTable(string& tablename);  /* 将对应的表字段获取出来 */

	string& setFilter(string& filter);

	string& getTable();

	int select();
	int removeColumn(int column);
	int removeColumns(int column, int count);

	void showFields();
	void showResultColumn(MYSQL_RES *result); /* 将result转化成一个通用的Slqrecord类 */
	void showResultRow(MYSQL_RES *result);

public:
	Sqldatabase m_db;

private:
	string m_tablename;

	MySqlResult m_mysqlresult;
};

#endif