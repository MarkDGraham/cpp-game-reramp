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
	Input_None,
	Input_Up,
	Input_Down,
	Input_Left,
	Input_Right
};

inputDirection currentDirection = Input_None;

const int gridWidth = 25, gridHeight = 15;

enum worldTile {
	Tile_Wall,
	Tile_Empty
};

worldTile worldGrid[gridHeight][gridWidth] = {
{Tile_Wall, Tile_Wall, Tile_Wall, Tile_Wall, Tile_Wall, Tile_Wall, Tile_Wall, Tile_Wall, Tile_Wall, Tile_Wall, Tile_Wall, Tile_Wall, Tile_Wall, Tile_Wall, Tile_Wall, Tile_Wall, Tile_Wall, Tile_Wall, Tile_Wall, Tile_Wall, Tile_Wall, Tile_Wall, Tile_Wall, Tile_Wall, Tile_Wall},
{Tile_Wall, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Wall},
{Tile_Wall, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Wall},
{Tile_Wall, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Wall},
{Tile_Wall, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Wall},
{Tile_Wall, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Wall},
{Tile_Wall, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Wall},
{Tile_Wall, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Wall},
{Tile_Wall, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Wall},
{Tile_Wall, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Wall},
{Tile_Wall, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Wall},
{Tile_Wall, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Wall},
{Tile_Wall, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Wall},
{Tile_Wall, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Empty, Tile_Wall},
{Tile_Wall, Tile_Wall, Tile_Wall, Tile_Wall, Tile_Wall, Tile_Wall, Tile_Wall, Tile_Wall, Tile_Wall, Tile_Wall, Tile_Wall, Tile_Wall, Tile_Wall, Tile_Wall, Tile_Wall, Tile_Wall, Tile_Wall, Tile_Wall, Tile_Wall, Tile_Wall, Tile_Wall, Tile_Wall, Tile_Wall, Tile_Wall, Tile_Wall}
}; 

void ProcessInput();

void Update(Player&);

void Render(const Player&, int);

void ClearScreen();

int main()
{
	bool running = true;
	int frame = 0;
	constexpr int FRAME_DELAY_MS = 500;
	
	Player player{1, 1};
	
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
			currentDirection = Input_Up;
			break;
		case 'a':
			currentDirection = Input_Left;
			break;
		case 's':
			currentDirection = Input_Down;
			break;
		case 'd':
			currentDirection = Input_Right;
			break;
		default:
			currentDirection = Input_None;
	}
}

void Update(Player& player){
		int targetX = player.x;
	int targetY = player.y;

	switch (currentDirection)
	{
		case Input_Up:    targetY--; break;
		case Input_Down:  targetY++; break;
		case Input_Left:  targetX--; break;
		case Input_Right: targetX++; break;
		default: break;
	}

	if (targetX >= 0 && targetX < gridWidth &&
	    targetY >= 0 && targetY < gridHeight &&
	    worldGrid[targetY][targetX] == Tile_Empty)
	{
		player.x = targetX;
		player.y = targetY;
	}

	currentDirection = Input_None;
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
