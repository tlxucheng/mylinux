#include <iostream>
#include <typeinfo>

using namespace std;

class CallUa
{
public:
   typedef struct _callout
   {
	   unsigned long ringtime;
	   unsigned long confirmtime; 
   }callout;

   typedef struct _callin
   {
	   unsigned long ringtime;
	   unsigned long confirmtime; 
   }callin;
	
	void show_callout()
	{
		kind_ = 0;
	    callout& data = Data<callout>();
		cout << "callout" << data.ringtime << endl;
	}

	void show_callin()
	{
		kind_ = 1;
	    callin& data = Data<callin>();
		cout << "callin" << data.ringtime << endl;
	}
	
	CallUa(&test) : kind_(0), data_(test) { }
	
private:

    template <typename ToType>
	ToType& Data()
	{
		return const_cast<ToType&>(static_cast<const CallUa&>(*this).Data<ToType>());
	}

   template <typename ToType>
   const ToType& Data() const
   {
       bool okay;
	   switch(kind_)
	   {
       case 0: okay = (typeid(callout) == typeid(ToType)); break;
	   case 1: okay = (typeid(callin) == typeid(ToType)); break;
	   default: okay = false;
	   }
	   return *static_cast<ToType*>(data_);
   }

   int kind_;
   void *data_;
};



int main()
{
	CallUa test;
    
	
    return 0;
}