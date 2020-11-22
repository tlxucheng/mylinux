#include "stdafx.h"
#include "anytype.h"

AnyType::AnyType(int i)
{
	this->data.i = i;
}

AnyType::AnyType(char *str)
{
	//this->data.ptr = (void *)str;
	//this->data.ptr = *reinterpret_cast<void *const*>(str); //如果是const char *str，如何转换
	this->data.ptr = static_cast<void *>(str);
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
	string str = static_cast<char *>(this->data.ptr);

	return str;
}
