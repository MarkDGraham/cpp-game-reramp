// Console-based game engine prototype
// Focus: game loop, input intent, grid movement

#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>

struct Player
{
	int x, y;
};

enum inputDirection {
	None,
	Up,
	Down,
	Left,
	Right
};

inputDirection currentDirection = None;

const int gridWidth = 25, gridHeight = 15;

void ProcessInput();

void Update(Player&);

void Render(const Player&, int);

void ClearScreen();

int main()
{
	bool running = true;
	int frame = 0;
	constexpr int FRAME_DELAY_MS = 500;
	
	Player player{0, 0};
	
	while (running)
	{
		
		ProcessInput();
		Update(player);
		ClearScreen();
		Render(player, frame++);
		
		
		std::this_thread::sleep_for(
			std::chrono::milliseconds(FRAME_DELAY_MS)
		);
	}

	return 0;
}

void ProcessInput(){
	char input;
	std::cin >> input;
	switch (input){
		case 'w':
			currentDirection = Up;
			break;
		case 'a':
			currentDirection = Left;
			break;
		case 's':
			currentDirection = Down;
			break;
		case 'd':
			currentDirection = Right;
			break;
		default:
			currentDirection = None;
	}
}

void Update(Player& player){
	switch(currentDirection) {
		case Up: // Up
			if(player.y >= 1)
				player.y -= 1;
			break;
		case Down: // Down
			if(player.y < gridHeight - 1)
				player.y += 1;
			break;
		case Left: // Left
			if(player.x >= 1)
				player.x -= 1;
			break;
		case Right: // Right
			if(player.x < gridWidth - 1)
				player.x += 1;
			break;
		case None:
			break;
	}
	currentDirection = None;
}

void Render(const Player& player, int frame){
	std::cout << "Frame: " << frame << std::endl;
	std::cout << "Player position: (" 
	          << player.x << ", "
			  << player.y << ")" << std::endl;
}

void ClearScreen()
{
	std::system("clear");
}



