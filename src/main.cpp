// Console-based game engine prototype
// Focus: game loop, input intent, grid movement

#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <vector>

struct Player {
	int x, y;
};

struct Enemy {
	int x, y;
};

enum class InputDirection {
	None,
	Up,
	Down,
	Left,
	Right
};

const int gridWidth = 25, gridHeight = 15;

enum class WorldTile {
	Wall,
	Empty
};

WorldTile worldGrid[gridHeight][gridWidth] = {
{WorldTile::Wall, WorldTile::Wall, WorldTile::Wall, WorldTile::Wall, WorldTile::Wall, WorldTile::Wall, WorldTile::Wall, WorldTile::Wall, WorldTile::Wall, WorldTile::Wall, WorldTile::Wall, WorldTile::Wall, WorldTile::Wall, WorldTile::Wall, WorldTile::Wall, WorldTile::Wall, WorldTile::Wall, WorldTile::Wall, WorldTile::Wall, WorldTile::Wall, WorldTile::Wall, WorldTile::Wall, WorldTile::Wall, WorldTile::Wall, WorldTile::Wall},
{WorldTile::Wall, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Wall},
{WorldTile::Wall, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Wall},
{WorldTile::Wall, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Wall},
{WorldTile::Wall, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Wall},
{WorldTile::Wall, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Wall},
{WorldTile::Wall, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Wall},
{WorldTile::Wall, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Wall},
{WorldTile::Wall, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Wall},
{WorldTile::Wall, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Wall},
{WorldTile::Wall, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Wall},
{WorldTile::Wall, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Wall},
{WorldTile::Wall, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Wall},
{WorldTile::Wall, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Empty, WorldTile::Wall},
{WorldTile::Wall, WorldTile::Wall, WorldTile::Wall, WorldTile::Wall, WorldTile::Wall, WorldTile::Wall, WorldTile::Wall, WorldTile::Wall, WorldTile::Wall, WorldTile::Wall, WorldTile::Wall, WorldTile::Wall, WorldTile::Wall, WorldTile::Wall, WorldTile::Wall, WorldTile::Wall, WorldTile::Wall, WorldTile::Wall, WorldTile::Wall, WorldTile::Wall, WorldTile::Wall, WorldTile::Wall, WorldTile::Wall, WorldTile::Wall, WorldTile::Wall}
};

enum class RenderTile {
	Empty,
	Wall,
	Player,
	Invalid
};

enum class ActionIntent {
	Move,
	Wait,
	None
};

struct InputIntent {
	ActionIntent action;
	InputDirection direction;
};

enum class MovementResult {
	Success,
	OutOfBounds,
	Blocked
};

struct RenderBuffer {
	RenderTile tile[gridHeight][gridWidth];
};

void ResolveWait();
void ProcessInput(InputIntent&);
void Update(Player&, InputIntent&);
void Render(const RenderBuffer&);
void GridTile(RenderTile);
MovementResult MovementResolution(Player&, InputDirection);
void BuildRenderBuffer(RenderBuffer& buffer, const Player& player);
void ClearScreen();

int main() {
	bool running = true;
	constexpr int FRAME_DELAY_MS = 500;
	
	Player player{1, 1};
	std::vector<Enemy> Enemies;
	InputIntent intent{ActionIntent::None, InputDirection::None};
	
	while (running)
	{
		ProcessInput(intent);
		Update(player, intent);
		
		RenderBuffer buffer;
		BuildRenderBuffer(buffer, player);
		
		ClearScreen();
		Render(buffer);
		
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
			intent.action = ActionIntent::Move; 
			intent.direction = InputDirection::Up;
			break;
		case 'a':
			intent.action = ActionIntent::Move;
			intent.direction = InputDirection::Left;
			break;
		case 's':
			intent.action = ActionIntent::Move;
			intent.direction = InputDirection::Down;
			break;
		case 'd':
			intent.action = ActionIntent::Move;
			intent.direction = InputDirection::Right;
			break;
		case 'e':
			intent.action = ActionIntent::Wait;
			intent.direction = InputDirection::None;
			break;
		default:
			intent.action = ActionIntent::None;
			intent.direction = InputDirection::None;
	}
}

void Update(Player& player, InputIntent& intent) {
	switch(intent.action) { 
		case ActionIntent::Move: 
		{
			MovementResult LastMovementResult =
				MovementResolution(player, intent.direction);
			intent.action = ActionIntent::None;
			break;
		}
		case ActionIntent::Wait:
		{
			ResolveWait();
			intent.action = ActionIntent::None;
			break;
		}
		default:
			intent.action = ActionIntent::None;
	}
}

void BuildRenderBuffer(RenderBuffer& buffer, const Player& player) {
	for(int row = 0; row < gridHeight; row++)
	{
		for(int col = 0; col < gridWidth; col++)
		{
			if(row == player.y && col == player.x)
				buffer.tile[row][col] = RenderTile::Player;
			else
				switch (worldGrid[row][col])
				{
					case WorldTile::Empty: 
						buffer.tile[row][col] = RenderTile::Empty; 
						break;
					case WorldTile::Wall: 
						buffer.tile[row][col] = RenderTile::Wall; 
						break;
					default: 
						buffer.tile[row][col] = RenderTile::Invalid;
						break;
				}
		}
	}
}

void ResolveWait() {
	return;
}

void Render(const RenderBuffer& buffer) {
	for(int row = 0; row < gridHeight; row++) {
		for(int col = 0; col < gridWidth; col++)
			GridTile(buffer.tile[row][col]);
		std::cout << std::endl;
	}
}

void GridTile(RenderTile renderImg) {
	switch (renderImg)
	{
		case RenderTile::Empty: std::cout << " "; break;
		case RenderTile::Wall: std::cout << "@"; break;
		case RenderTile::Player: std::cout << "+"; break;
		default: std::cout << "Invalid Render State!"; break;
	}
}

MovementResult MovementResolution(Player& player, InputDirection direction) {
	int targetX = player.x;
	int targetY = player.y;

	switch (direction) {
		case InputDirection::Up:    targetY--; break;
		case InputDirection::Down:  targetY++; break;
		case InputDirection::Left:  targetX--; break;
		case InputDirection::Right: targetX++; break;
		default: break;
	}

	if(targetX < 0 || targetX >= gridWidth ||
	   targetY < 0 || targetY >= gridHeight) {
		return MovementResult::OutOfBounds;
	}
	else if(worldGrid[targetY][targetX] != WorldTile::Empty) {
		return MovementResult::Blocked;
	}
	else {
		player.x = targetX;
		player.y = targetY;
		return MovementResult::Success;
	}
}

void ClearScreen() {
	std::system("clear");
}

