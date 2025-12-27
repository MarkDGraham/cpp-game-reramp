#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>

struct Player
{
	float x, y, speed;
};

void ProcessInput();

void Update(Player&, float);

void Render(const Player&, int);


int main()
{
	bool running = true;
	int frame = 0;
	constexpr int FRAME_DELAY_MS = 500;

	using clock = std::chrono::steady_clock;
	
	auto lastTime = clock::now();
	
	Player player;
	player.x = 0.0f;
	player.y = 0.0f;
	player.speed = 2.0f;
	
	while (running)
	{
		auto currentTime = clock::now();
		std::chrono::duration<float> delta = currentTime - lastTime;
		float deltaTime = delta.count();
		lastTime = currentTime;
		
		ProcessInput();
		Update(player, deltaTime);
		Render(player, frame++);
		
		
		std::this_thread::sleep_for(
			std::chrono::milliseconds(FRAME_DELAY_MS)
		);
	}

	return 0;
}

void ProcessInput(){

}

void Update(Player& player, float deltaTime){
	player.x += player.speed * deltaTime;
}

void Render(const Player& player, int frame){
	std::cout << "Frame: " << frame << std::endl;
	std::cout << "Player position: (" 
	          << player.x << ", "
			  << player.y << ")" << std::endl;
}



