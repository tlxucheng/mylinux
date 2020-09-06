#include <iostream>

using namespace std;

typedef enum
{
    MYSQL = 0,
    ORACLE,
    SQLSERVER
}DB_TYPE;

class databases
{
public:
    virtual void connect() = 0;
};

class mysql:public databases
{
public:
    void connect()
    {
        cout << "mysql connect" << endl;
    }
};

class oracle:public databases
{
public:
    void connect()
    {
        cout << "oracle connect" << endl;
    }
};

class sqlserver:public databases
{
public:
    void connect()
    {
        cout << "sqlserver connect" << endl;
    }
};

class dbfactory
{
public:
    databases *Create(DB_TYPE db_type)
    {
        switch(db_type)
        {
        case MYSQL:
            return new mysql;
            break;
        case ORACLE:
            return new oracle;
            break;
        case SQLSERVER:
            return new sqlserver;
            break;
        default:
            break;
        }

        return NULL;
    }

    void destory(databases *pDb)
    {
        if(pDb)
        {
            delete pDb;
            pDb = NULL;
        }
    }
   
};

int main()
{
    dbfactory    dbf;
    databases    *mysql_db;
    databases    *oracle_db;
    databases    *sqlserver_db;

    mysql_db = dbf.Create(MYSQL);
    mysql_db->connect();
    dbf.destory(mysql_db);

    oracle_db = dbf.Create(ORACLE);
    oracle_db->connect();
    dbf.destory(oracle_db);

    sqlserver_db = dbf.Create(SQLSERVER);
    sqlserver_db->connect();
    dbf.destory(sqlserver_db);

    return 0;
}

