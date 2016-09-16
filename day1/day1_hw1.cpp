#include <iostream>
#include <iomanip>
#include <string>


int main()
{
	int width, location;
	std::string direction;

	std::cin>> width;
	std::cin>> location;
	std::cin>> direction;

	int total = width * width;
	int arr[width][width];
	int arr2[width][width];
	int num = 1 , i=0 , j=0, z=0, it = width;
	int *ptr_i=&i, *ptr_j=&j, *ptr_num=&num;


	for(j=j; j < it ; j++,num++)
		arr[i][j]=num;
	it--;
	j--;
	// std::cout<< i<<"."<<j<<std::endl;


	while(num < total)
	{
		z=0;
		while(z < it){
			*ptr_i+=1;
			arr[*ptr_i][*ptr_j]=*ptr_num;
			*ptr_num +=1 ;
			z++;
		}
		// std::cout<< i<<"."<<j<<std::endl;

		z=0;
		while(z < it){
			*ptr_j-=1;
			arr[*ptr_i][*ptr_j]=*ptr_num;
		    z++;
			*ptr_num+=1;
		}
		// std::cout<< i<<"."<<j<<std::endl;

		it--;


		if(*ptr_num==total)
			break;


		z=0;
		while(z < it){
			*ptr_i-=1;
            arr[*ptr_i][*ptr_j]=*ptr_num;
            z++;
			*ptr_num+=1;
        }
		// std::cout<< i<<"."<<j<<std::endl;
		z=0;
		while(z < it){
			*ptr_j+=1;
			arr[*ptr_i][*ptr_j]=*ptr_num;
			z++;
			*ptr_num+=1;
		}
		// std::cout<< i<<"."<<j<<std::endl;
		it--;
	}


	if(location == 0)//left top
	{
        if(direction == "CC"){
	    	for(int x=0; x<width; x++)
		        for(int y=0; y<width; y++)
		            arr2[y][x]= arr[x][y];
		    for(int x=0; x<width; x++)
		        for(int y=0; y<width; y++)
	            	arr[x][y]= arr2[x][y];
        }

	}
	else if(location == 1)//right top
	{
		for(int x=0; x<width; x++)
	        for(int y=0; y<width; y++)
	            arr2[x][y]= arr[x][width-y-1];
	    for(int x=0; x<width; x++)
	        for(int y=0; y<width; y++)
            	arr[x][y]= arr2[x][y];

        if(direction == "C"){
			for(int x=0; x<width; x++)
		        for(int y=0; y<width; y++)
		            arr2[x][y]= arr[width-y-1][width-x-1];
		    for(int x=0; x<width; x++)
		        for(int y=0; y<width; y++)
	            	arr[x][y]= arr2[x][y];
        }

	}


	else if(location == 2)//right bottom
	{
		for(int x=0; x<width; x++)
	        for(int y=0; y<width; y++)
	            arr2[x][y]= arr[width-y-1][width-x-1];
	    for(int x=0; x<width; x++)
	        for(int y=0; y<width; y++)
	        	arr[x][y]= arr2[x][y];

	    if(direction == "C"){
    		for(int x=0; x<width; x++)
    	        for(int y=0; y<width; y++)
    	            arr2[x][y]= arr[y][x];
    	    for(int x=0; x<width; x++)
    	        for(int y=0; y<width; y++)
    	        	arr[x][y]= arr2[x][y];

	    }

	}
	else if(location == 3)//left bottom
	{
		for(int x=0; x<width; x++)
	        for(int y=0; y<width; y++)
	            arr2[x][y]= arr[width-x-1][y];
	    for(int x=0; x<width; x++)
	        for(int y=0; y<width; y++)
            arr[x][y]= arr2[x][y];

        if(direction == "C"){
        	for(int x=0; x<width; x++)
		        for(int y=0; y<width; y++)
		            arr2[x][y]= arr[width-y-1][width-x-1];
		    for(int x=0; x<width; x++)
		        for(int y=0; y<width; y++)
	            	arr[x][y]= arr2[x][y];
        }

	}


	//printing
	for(int x=0; x<width; x++)
	{
		for(int y=0; y<width; y++)
		{
			std::cout <<std::setfill(' ') <<std::setw(4) << arr[x][y];
		}
		std::cout<<std::endl;
	}


	return 0;

}
