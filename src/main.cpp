#include <iostream>
#include <thread>
#include <chrono>

int main()
{
	bool running = true;
	int frame = 0;
	
	
	while (running)
	{
		std::cout << "Frame: " << frame++ << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	return 0;
}
