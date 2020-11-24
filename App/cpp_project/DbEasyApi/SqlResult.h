#pragma once

#ifndef SQLRESULT_H
#define SQLRESULT_H

#include <iostream>
#include <string>

using namespace std;

class SqlResult
{
public:
	virtual bool reset(const string& sqlquery) = 0;
private:

};



#endif

