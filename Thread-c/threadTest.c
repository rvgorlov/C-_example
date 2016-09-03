#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>	
#include <string>
#include <iostream>

#define ERROR_CREATE_THREAD -11
#define ERROR_JOIN_THREAD   -12
#define SUCCESS        0

class threadHandle
{
public:
	int addThread() 
	{
		pthread_t thread; 
		long answer = 0; 
   		
   		threadData * data = malloc(sizeof(*data));
   		data->one = 2; 
   		data->two = 3;
   		data->str = "123"; 

   		int status = pthread_create(&thread, NULL, this->call_sum, data);
   		if (status != 0)
   		{
   			std::cout << "thread error"; 
   			exit(ERROR_CREATE_THREAD); 
   		}

   		void *r;
   		pthread_join(thread, &r);
   		answer = (long) r; 
	} 
private: 
	static void * call_sum (void *dateStruct)
	{
		struct threadData * data =  (__typeof__(data))dateStruct;
		int sum = data->one + data->two; 
		std::cout << sum << " " << data->one << " " << data->two << std::endl;  
		free(dateStruct);
		return (void *)(long) sum;  
	}

	struct threadData 
	{
		int one; 
		int two; 
		std::string str; 
	};
};

int main (int argc, char *av[])
{
	threadHandle hand; 
	long answer = hand.addThread(); 
	std::cout << answer << std::endl; 
	    



	return 0;
}