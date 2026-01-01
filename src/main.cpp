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

enum renderTiles {
	Render_Empty,
	Render_Wall,
	Render_Player,
	Render_Invalid
};

void ProcessInput();

void Update(Player&);

void Render(const Player&, int);

void GridTile(renderTiles);

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
	for(int row = 0; row < gridHeight; row++)
	{
		for(int col = 0; col < gridWidth; col++)
		{
			if(row == player.y && col == player.x)
				GridTile(Render_Player);
			else
				switch (worldGrid[row][col])
				{
					case Tile_Empty: GridTile(Render_Empty); break;
					case Tile_Wall: GridTile(Render_Wall); break;
					default: GridTile(Render_Invalid); break;
				}
		}
		std::cout << std::endl;
	}
}

void GridTile(renderTiles renderImg)
{
	switch (renderImg)
	{
		case Render_Empty: std::cout << " "; break;
		case Render_Wall: std::cout << "@"; break;
		case Render_Player: std::cout << "+"; break;
		default: std::cout << "Invlaid Render State!"; break;
	}
}

void ClearScreen()
{
	std::system("clear");
}
