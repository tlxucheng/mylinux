#include <iostream>

using namespace std;

class databases
{
public:
    virtual void show() = 0;
};

class mysql:public databases
{
public:
    void show()
	{
	    cout << "this is mysql class" << endl;
	}
};

class oracle:public databases
{
public:
    void show()
	{
	    cout << "this is oracle class" << endl;
	}
}; 

class program_lang
{
public:
    virtual void show() = 0;
};

class program_cpp:public program_lang
{
public:
    void show()
	{
	    cout << "this is program_cpp class" << endl;
	}
};

class program_java:public program_lang
{
public:
    void show()
	{
	    cout << "this is grogram_java class" << endl;
	}
}; 

class abstract_factoy
{
public:
    virtual databases *create_db() = 0;    
    virtual program_lang *create_grogram_lang() = 0;
};

class cpp_factory:public abstract_factoy
{
public:
    databases *create_db()
    {
        return new mysql;
    }

    program_lang *create_grogram_lang()
    {
        return new program_cpp;
    }
};

class java_factory:public abstract_factoy
{
public:
    databases *create_db()
    {
        return new oracle;
    }

    program_lang *create_grogram_lang()
    {
        return new program_java;
    }
};

int main()
{
    cpp_factory  *test_cpp_factory  = new cpp_factory;
    databases    *test_db           = NULL; 
    program_lang *test_program_lang = NULL;
        
    test_db = test_cpp_factory->create_db();
    test_db->show();
    test_program_lang = test_cpp_factory->create_grogram_lang();
    test_program_lang->show();

    delete(test_cpp_factory);
    delete(test_db);
    delete(test_program_lang);

    java_factory  *test_java_factory  = new java_factory;
    
    test_db = test_java_factory->create_db();
    test_db->show();
    test_program_lang = test_java_factory->create_grogram_lang();
    test_program_lang->show();

    delete(test_java_factory);
    delete(test_db);
    delete(test_program_lang);

    return 0;
}

