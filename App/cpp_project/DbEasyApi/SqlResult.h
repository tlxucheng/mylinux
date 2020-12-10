#pragma once

#ifndef SQLRESULT_H
#define SQLRESULT_H

#include "AnyType.h"

#include <iostream>
#include <string>

using namespace std;

class SqlResult
{
public:
	virtual bool reset(const string& sqlquery) = 0;
	virtual AnyType data(int field) = 0;
private:

};



#endif

