/* https://github.com/ggicci/jsonla */

#include <iostream>  
#include "jsonla.h"  
  
using namespace std;  
using namespace ggicci;  
  
int main(int argc, char const *argv[])  
{ 
    Json json = Json::Parse("{\"id\": 1, \"name\": \"Ggicci\"}");

    cout << json.ToString() << endl;
    cout << json["id"].AsInt() << endl; 
    cout << json["name"].AsString() << endl;  

    Json json2 = Json::Parse("{}");
    
    json2.AddProperty("id", Json("10"));
    json2.AddProperty("name", Json("xc"));
    cout << json.ToString() << endl;

    return 0;  
}  
