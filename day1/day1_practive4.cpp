#include <iostream>
#include <vector>

int main()
{
	std::vector<int> v{};
	std::vector<int> result{};
	int input;	
	while(std::cin>>input)
		if (input != -1)
			v.push_back(input);
		else
			break;

	int len = v.size();

	for(int i=0; i<len ; i++)
		if (i != len-i-1)
			v[i] += v[len-i-1];
    if(len%2==0)
		for(int i=0; i < len/2 ; i++)
			result.push_back(v[i]);
	else
		for(int i=0; i< (len+1)/2 ; i++)
			result.push_back(v[i]);
	for(auto it : result)
		std::cout << it << " ";
	std::cout<<""<< std::endl;
	return 0;
}

