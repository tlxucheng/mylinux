#include <iostream>

using namespace std;

class MysqlDb
{
public:
    void connet()
    {
        cout << "mysql class connect"<< endl;
    }
};

class SqlStatement
{
public:
    void select()
    {
        cout << "SqlStatement class select"<< endl;
    }
};

class GetDataFromDb
{
public:
    void GetData()
    {
        m_mysqldb.connet();
        m_sqlstatement.select();
    }
private:
    MysqlDb m_mysqldb;
    SqlStatement m_sqlstatement;
};

int main()
{
    GetDataFromDb test;

    test.GetData();

    return 0;
}

