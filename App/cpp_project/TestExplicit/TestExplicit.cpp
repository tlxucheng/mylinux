// TestExplicit.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

using namespace std;

class TestExplicit
{
public:
	TestExplicit() 
	{

	}

	explicit TestExplicit(int a)
	{
		value1 = a;
	}

	TestExplicit(int a, double b)
	{
		value1 = a;
		value2 = b;
	}

	void show()
	{
		cout << "value1: " << value1 << endl;
		cout << "value2: " << value2 << endl;
	}

private:
	int value1;
	double value2;

};

int main()
{
	TestExplicit test(10);
	test.show();

    return 0;
}

