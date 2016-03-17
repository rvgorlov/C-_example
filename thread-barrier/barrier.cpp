#include <iostream>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <mutex>

using namespace std;

class barrier {

const unsigned int threadCount;
std::atomic<unsigned int>threadsWaiting; 
bool isNotWaiting;
std::condition_variable waitVariable;
std::mutex mutex;

public:
	barrier(unsigned int n) : threadCount(n) {
		threadsWaiting = 0;
  		isNotWaiting = false;
	}

	barrier(const barrier &) = delete;
 	
 	void wait() {
  		if (threadsWaiting.fetch_add(1) >= threadCount - 1) {
			isNotWaiting = true;
   			waitVariable.notify_all();
   			threadsWaiting.store(0);
 		} else {
  			std::unique_lock<std::mutex> lock(mutex);
  			waitVariable.wait(lock,[&]{ return isNotWaiting;});
 		}
	}
};


barrier *myBarrier;
mutex coutMutex; 

void print (int i) {
	coutMutex.lock(); 
	cout << "Поток " << i << " До барьера" << endl; 
	coutMutex.unlock(); 
	myBarrier->wait(); 
	coutMutex.lock(); 
	cout << "Поток " << i << " После" << endl;
	coutMutex.unlock();   
}

int main() {
	myBarrier = new barrier(100);
	thread threads[100];
	for (int i = 0; i < 100; ++i)
	{
		thread thr(print, i);
		threads[i] = move(thr);  
	}

	for (int i = 0; i < 100; ++i)
	{
		threads[i].join(); 
	}

    delete myBarrier;
	return 0;
}