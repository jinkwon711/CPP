http://gaeddong2.tistory.com/entry/%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98-%EA%B3%84%EC%82%B0%EA%B8%B0-%EA%B5%AC%ED%98%84
#include <iostream>
#include <string>

int main()
{
	//input part
  	std::string cal;
	getline(std::cin,cal);
	std::string newCal="";


	//sizing array & deleting spaces
	unsigned int plus = 1, multiple = 1, answer=0;
	for (auto &i : cal)
		if (isspace(i)==false)
			newCal+=i;
	for(auto i : cal)
		if (i == '+')
			plus++;
		else if(i == '*')
			multiple++;

	//creating array
	unsigned int arr[plus][multiple];
	for(auto &i:arr)
		for(auto &j:i)
			j=0-1;

	newCal+="*";//for loop below, + or * is actually replacing the value of array
				//and at the end of the string there is no + or * , so + was added.

	//put info in 2d array addition by row, multiplication by col
	unsigned int row = 0, col=0, temp=0;
	for(unsigned int i = 0; i<newCal.length();i++)
	{
		if (newCal[i] == '+')
		{
			arr[row][col] = temp;
			temp=0;
			row++;
			col=0;
		}
		else if(newCal[i] == '*')
		{
			arr[row][col] = temp;
			temp=0;
			col++;
		}
		else
		{
			temp=temp*10;
			temp += newCal[i]-'0';
		}
	}
	// multiplying cols and adding that values to the answer
    for(unsigned int i=0; i<plus;i++)
	{
		for(unsigned int j=1; j<multiple; j++)
			if (arr[i][j] != 0-1)
				arr[i][0]*=arr[i][j];
		answer+=arr[i][0];
	}

	//result

	std::cout<<answer<<std::endl;
	return 0;

}
