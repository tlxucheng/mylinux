#pragma once

#ifndef SQLDRIVER_H
#define SQLDRIVER_H

#pragma comment(lib, "libmysql.lib")

#include <string>
#include "mysql.h"

using namespace std;

class SqlDriver
{
public:
	//SqlDriver();
	virtual ~SqlDriver();

	virtual bool open(string& host, string& user, string& password, string& db, unsigned int port) = 0;

private:

};

#endif 