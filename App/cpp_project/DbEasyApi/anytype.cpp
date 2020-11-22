#include "stdafx.h"
#include "anytype.h"

AnyType::AnyType(int i)
{
	this->data.i = i;
}

AnyType::AnyType(const char *str)
{
	this->data.ptr = (void *)str;
}

AnyType::~AnyType()
{

}

int AnyType::toInt()
{
	return this->data.i;
}

string AnyType::toString()
{
	//return this->data.i;
	string str;

	return str;
}
