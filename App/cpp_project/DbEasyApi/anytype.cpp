#include "stdafx.h"
#include "anytype.h"

AnyType::AnyType(int i)
{
	this->data.i = i;
}

AnyType::AnyType(char *str)
{
	//this->data.ptr = (void *)str;
	//this->data.ptr = *reinterpret_cast<void *const*>(str); //�����const char *str�����ת��
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
