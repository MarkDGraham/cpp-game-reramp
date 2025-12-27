#include <iostream>
#include <thread>
#include <chrono>

void ProcessInput();

void Update(float);

void Render(int);

int main()
{
	bool running = true;
	int frame = 0;
	constexpr int FRAME_DELAY_MS = 500;

	using clock = std::chrono::steady_clock;
	
	auto lastTime = clock::now();
	
	while (running)
	{
		auto currentTime = clock::now();
		std::chrono::duration<float> delta = currentTime - lastTime;
		float deltaTime = delta.count();
		lastTime = currentTime;
		
		ProcessInput();
		Update(deltaTime);
		Render(frame++);
		
		
		std::this_thread::sleep_for(
			std::chrono::milliseconds(FRAME_DELAY_MS)
		);
	}

	return 0;
}

void ProcessInput(){

}

void Update(float deltaTime){
	std::cout << "Delta: " << deltaTime << std::endl;
}

void Render(int frame){
	std::cout << "Frame: " << frame << std::endl;
}



