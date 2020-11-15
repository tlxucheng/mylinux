// TestPolymorphism.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <memory>

using namespace std;

class Father
{
public:
	virtual ~Father()                                        /* ����Ƕ��ؼ̳У���Щ��Ҫ����Ϊ�麯���� */
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

	shared_ptr<Father>m_p;  /* http://c.biancheng.net/view/430.html  ����ָ�� */
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

