#include <iostream>
#include <unordered_map>

int main()
{
    std::unordered_map<char, int> romanMap{{'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}};

    std::cout << romanMap[('C')] << std::endl;

	return 0;
}
