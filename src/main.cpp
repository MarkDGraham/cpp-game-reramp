// Console-based game engine prototype
// Focus: game loop, input intent, grid movement

#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>

struct Player {
	int x, y;
};

enum inputDirection {
	Input_None,
	Input_Up,
	Input_Down,
	Input_Left,
	Input_Right
};

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

enum ActionIntent {
	Intent_Move,
	Intent_None
};

enum movementActions {
	Movement_Move,
	Movement_Block
};

struct InputIntent {
	ActionIntent action;
	inputDirection direction;
};

enum class MovementResult {
	Success,
    OutOfBounds,
    Blocked
};

void ProcessInput(InputIntent&);

void Update(Player&, InputIntent&);

void Render(const Player&, int);

void GridTile(renderTiles);

MovementResult MovementResolution(Player&, inputDirection);

void ClearScreen();

int main() {
	bool running = true;
	int frame = 0;
	constexpr int FRAME_DELAY_MS = 500;
	
	Player player{1, 1};
	InputIntent intent{Intent_None, Input_None};
	
	while (running)
	{
		
		ProcessInput(intent);
		Update(player, intent);
		ClearScreen();
		Render(player, frame++);
		
		
		std::this_thread::sleep_for(
			std::chrono::milliseconds(FRAME_DELAY_MS)
		);
	}

	return 0;
}

void ProcessInput(InputIntent& intent) {
	char input;
	std::cin >> input;
	switch (input){
		case 'w':
			intent.action = Intent_Move; 
			intent.direction = Input_Up;
			break;
		case 'a':
			intent.action = Intent_Move;
			intent.direction = Input_Left;
			break;
		case 's':
			intent.action = Intent_Move;
			intent.direction = Input_Down;
			break;
		case 'd':
			intent.action = Intent_Move;
			intent.direction = Input_Right;
			break;
		default:
			intent.action = Intent_None;
			intent.direction = Input_None;
	}
}

void Update(Player& player, InputIntent& intent) {
	
	if(intent.action == Intent_Move) { 
		MovementResult Outcome = MovementResolution(player, intent.direction);
		switch (Outcome){
			case MovementResult::Success: std::cout << "Movement Success!" << std::endl; break;
			case MovementResult::OutOfBounds: std::cout << "Out of bounds!" << std::endl; break;
			case MovementResult::Blocked: std::cout << "Movement blocked!" << std::endl; break;
			default: std::cout << "Invalid Action" << std::endl; break;
		}
		
		intent.action = Intent_None; 
	}
}

void Render(const Player& player, int frame) {
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

void GridTile(renderTiles renderImg) {
	switch (renderImg)
	{
		case Render_Empty: std::cout << " "; break;
		case Render_Wall: std::cout << "@"; break;
		case Render_Player: std::cout << "+"; break;
		default: std::cout << "Invlaid Render State!"; break;
	}
}

MovementResult MovementResolution(Player& player, inputDirection direction) {
	int targetX = player.x;
	int targetY = player.y;

	switch (direction) {
		case Input_Up:    targetY--; break;
		case Input_Down:  targetY++; break;
		case Input_Left:  targetX--; break;
		case Input_Right: targetX++; break;
		default: break;
	}

	if(targetX < 0 || targetX >= gridWidth ||
	    targetY < 0 || targetY >= gridHeight) {
		return MovementResult::OutOfBounds;
	} else if(worldGrid[targetY][targetX] != Tile_Empty) {
		return MovementResult::Blocked;
	} else {
		player.x = targetX;
		player.y = targetY;
		return MovementResult::Success;
	}
}

void ClearScreen() {
	std::system("clear");
}
