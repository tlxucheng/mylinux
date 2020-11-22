#pragma once
#ifndef  ANYTYPE_H
#define  ANYTYPE_H

#include <iostream>
#include <string>

using namespace std;

class AnyType
{
public:
	AnyType(int i);
	AnyType(char* str);
	~AnyType();

	int toInt();
	string toString();

private:
	union data
	{
		int i;
		void* ptr;
	}data;

	int type;
};


#endif //  ANYTYPE_H
