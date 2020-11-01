// LocalObjectReturnTest.cpp : 定义控制台应用程序的入口点。
//

/* https://www.cnblogs.com/alantu2018/p/8459250.html */

#include "stdafx.h"
#include <iostream>

using namespace std;

class Student
{
public:
	Student()
	{
		cout << "default constructor function is called" << endl;
	}

	Student(int num)
	{
		cout << "constructor function is called" << endl;

		this->num = num;
	}

	Student(const Student & c)
	{
		cout << "copy function is called" << endl;

		num = c.num;
	}

	~Student()
	{
		cout << "destructor function is called" << endl;
	}

	void show()
	{
		cout << "num: " << num << endl;
	}

private:
	int num;
};

Student getStu(int num)
{
	Student su(num);

	return su;
}

class Teacher
{
public:
	void show()
	{
		stu.show();
	}

public:
	Student stu;

private:
	int num;
};

int main()
{
	Student st = getStu(100);

	st.show();

	/*
	Teacher ter;

	ter.stu = getStu(100);
	ter.show();
	*/

    return 0;
}

