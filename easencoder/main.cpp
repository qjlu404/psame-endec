#include <iostream>
#include <Windows.h>
#include <thread>
#include <vector>
#include <string>
#include "../Encoder/Encoder.h" 
bool loading;
void whileloading()
{
	while (loading) 
	{
		std::cout << '|';
		Sleep(500);
		std::cout << '\b';
		std::cout << '/';
		Sleep(500);
		std::cout << '\b';
		std::cout << "-";
		Sleep(500);
		std::cout << "\b";
		std::cout << "\\";
		Sleep(500);
		std::cout << "\b";
		
		
	}
}
void enc(std::string input)
{
	encode(input, 0, 0, 1, 1, 1, 1);
}
int main()
{
	std::cout << "enter full alert text: ";
	std::string input;
	std::cin >> input;
	std::thread t1 (enc,input);
	loading = true;
	std::thread t2(whileloading);
	t1.join();
	loading = false; 
	t2.join();

	return 0;
}