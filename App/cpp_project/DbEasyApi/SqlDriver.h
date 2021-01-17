#pragma once

#ifndef SQLDRIVER_H
#define SQLDRIVER_H

#pragma comment(lib, "libmysql.lib")

#include <string>
#include "mysql.h"
#include "SqlResult.h"

using namespace std;

class SqlDriver
{
public:
	//SqlDriver();
	virtual ~SqlDriver();

	//virtual MYSQL*  getMysqlHandle() = 0; /* 不应该出现 MYSQL 类型函数 */
	virtual bool init() = 0;
	virtual bool open(string& host, string& user, string& password, string& db, unsigned int port) = 0;

	virtual SqlResult *createResult() const = 0;
private:

};

#endif 