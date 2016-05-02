#include <iostream>
#include <vector>
#include <exception>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
	try{
		vector<int> v(10);
		for (int i = 0; i < 10; ++i)
		{
			v.at(i) = 5; 
		}

		cout << v.at(10) << endl;
	}
	catch (exception& e) {
		cout << e.what() << endl;
		return 1;
	}
	catch (...) {
		cout << "Неизвестная ошибка" << endl;
		return 1; 
	}
	return 0;
}