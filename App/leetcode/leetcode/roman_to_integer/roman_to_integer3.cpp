#include <iostream>
#include <map>

int main()
{
    std::map<char, int> romanMap;

	romanMap.insert(std::pair<char, int>('I',1));
	romanMap.insert(std::pair<char, int>('C',100));

    std::cout << romanMap[('C')] << std::endl;

	return 0;
}
