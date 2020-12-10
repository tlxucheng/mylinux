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
	AnyType();
	~AnyType();

	enum Type {
		Char,
		Int,
		Long,
		Bool,
		Double,
		String,
	};

	int toInt();
	string toString();

private:
	union data
	{
		char c;
		unsigned char uc;
		short s;
		signed char sc;
		unsigned short us;
		int i;
		unsigned u;
		long l;
		unsigned long ul;
		bool b;
		double d;
		float f;


		void* ptr;
	}data;

	int type;
};


#endif //  ANYTYPE_H
