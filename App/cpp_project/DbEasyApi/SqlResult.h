#pragma once

#ifndef SQLRESULT_H
#define SQLRESULT_H

#include "AnyType.h"

#include <iostream>
#include <string>

using namespace std;

struct MyFields
{
	string name;
	int type;
};

class SqlResult
{
public:
	virtual bool reset(const string& sqlquery) = 0;
	virtual AnyType data(int field) = 0;
	
	/* test function */
	virtual void show_fileds() = 0;
	virtual void show_data(int index) = 0;
	virtual void show_data() = 0;
private:

};



#endif

