#include <iostream>
#include <string>

std::string result = "";
int main()
{
	std::string str;
	std::cin >> str;
	for(auto i:str)
		if (ispunct(i)==0)
				::result += i;
	std::cout << result << std::endl;
	return 0;
}
