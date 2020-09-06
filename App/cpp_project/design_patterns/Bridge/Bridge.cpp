#include <iostream>

using namespace std;

class statement
{
public:
    virtual ~statement() {}
    virtual void execute() = 0;
    
};

class select:public statement
{
public:
    void execute()
    {
        cout << "exec select sql" << endl;
    }
};

class insert:public statement
{
public:
    void execute()
    {
        cout << "exec insert sql" << endl;
    }
};

class update:public statement
{
public:
    void execute()
    {
        cout << "exec update sql" << endl;
    }
};


class db
{
public:
    virtual ~db() {}
    virtual void execute() = 0;    
};

class mysql:public db
{
public:
    mysql(statement *pStatement)
    {
        this->pStatement = pStatement;
    }
    
    ~mysql()
    {
        delete pStatement;
        pStatement = NULL;
    }

    void execute()
    {
        pStatement->execute();
    }
    
private:
    statement *pStatement = NULL;
};

class oracle:public db
{
public:
    oracle(statement *pStatement)
    {
        this->pStatement = pStatement;
    }
    
    ~oracle()
    {
        delete pStatement;
        pStatement = NULL;
    }

    void execute()
    {
        pStatement->execute();
    }
    
private:
    statement *pStatement = NULL;
};

class sqlserver:public db
{
public:
    sqlserver(statement *pStatement)
    {
        this->pStatement = pStatement;
    }
    
    ~sqlserver()
    {
        delete pStatement;
        pStatement = NULL;
    }

    void execute()
    {
        pStatement->execute();
    }
    
private:
    statement *pStatement = NULL;
};


int main()
{
     db *test = NULL;

     test = new mysql(new select());
     test->execute();
     delete test;
     
     test = new mysql(new insert());
     test->execute();
     delete test;

     test = new mysql(new update());
     test->execute();
     delete test;

     test = new oracle(new select());
     test->execute();
     delete test;
     
     test = new oracle(new insert());
     test->execute();
     delete test;

     test = new oracle(new update());
     test->execute();
     delete test;

     test = new sqlserver(new select());
     test->execute();
     delete test;
     
     test = new sqlserver(new insert());
     test->execute();
     delete test;

     test = new sqlserver(new update());
     test->execute();
     delete test;

     return 0;
}


