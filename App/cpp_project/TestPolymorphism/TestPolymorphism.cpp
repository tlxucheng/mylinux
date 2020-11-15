// TestPolymorphism.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <memory>

using namespace std;

class Father
{
public:
	virtual ~Father()                                        /* 如果是多重继承，哪些需要申明为虚函数？ */
	{
		cout << "deconstruction Father Class" << endl;
	}
private:
};

class Son : public Father
{
public:
	~Son()
	{
		cout << "deconstruction Son Class" << endl;
	}

private:
};

class Test
{
public:
	Test();
	~Test();  

	Test test_func()
	{
		Test tf;

		return tf;
	}
private:

	shared_ptr<Father>m_p;  /* http://c.biancheng.net/view/430.html  智能指针 */
};

Test::Test()
{
	m_p = make_shared<Son>();
}

Test::~Test()
{

}

int main()
{
	Test te;
	te.test_func();

    return 0;
}

