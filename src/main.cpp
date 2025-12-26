#include <iostream>
#include <thread>
#include <chrono>

int main()
{
	bool running = true;
	int frame = 0;
	constexpr int FRAME_DELAY_MS = 500;

	
	
	while (running)
	{
		std::cout << "Frame: " << frame++ << std::endl;
		std::this_thread::sleep_for(
			std::chrono::milliseconds(FRAME_DELAY_MS)
		);
	}

	return 0;
}
