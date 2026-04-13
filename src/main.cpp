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

struct World {
	WorldTile tiles[gridHeight][gridWidth] = 
	{
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
};

enum class RenderTile {
	Empty,
	Wall,
	Player,
	Enemy,
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
	PlayerCaptured,
	Blocked
};

struct RenderBuffer {
	RenderTile tile[gridHeight][gridWidth];
};

enum class EngineState {
	Running,
	GameOver
};

struct GameState {
	Player player;
	std::vector<Enemy> enemies;
	World world;
	InputIntent intent;
	EngineState state;
};

void ResolveWait();
void ProcessInput(InputIntent&);
MovementResult EnemyMovement(Enemy&, const Player&, const World&);
EngineState Update(GameState&);
void Render(const RenderBuffer&);
void GridTile(RenderTile);
MovementResult MovementResolution(Player&, InputDirection, const World&);
void BuildRenderBuffer(RenderBuffer&, const GameState&);
void ClearScreen();

int main() {
	constexpr int FRAME_DELAY_MS = 500;
	GameState currState {
	{1,1},
	{{15,5}, {20,10}, {6,12}},
	World{},
	{ActionIntent::None, InputDirection::None},
	EngineState::Running
	};
	
	while (currState.state == EngineState::Running)
	{
		ProcessInput(currState.intent);
		currState.state = Update(currState);
		
		RenderBuffer buffer;
		BuildRenderBuffer(buffer, currState);
	
		Render(buffer);
		
		std::this_thread::sleep_for(
			std::chrono::milliseconds(FRAME_DELAY_MS)
		);
	}
	
	std::cout << "Game Over" << std::endl;
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

EngineState Update(GameState& currentGameState) {
	switch(currentGameState.intent.action) { 
		case ActionIntent::Move: 
		{
			MovementResult LastMovementResult =
				MovementResolution(currentGameState.player, currentGameState.intent.direction, currentGameState.world);
			currentGameState.intent.action = ActionIntent::None;
			break;
		}
		case ActionIntent::Wait:
		{
			ResolveWait();
			currentGameState.intent.action = ActionIntent::None;
			break;
		}
		default:
			currentGameState.intent.action = ActionIntent::None;
	}
	
	for(Enemy& enemy : currentGameState.enemies) {
		MovementResult EnemyMovementResult = 
			EnemyMovement(enemy, currentGameState.player, currentGameState.world);
		if(EnemyMovementResult == MovementResult::PlayerCaptured)
			return EngineState::GameOver;
	}
	
	return EngineState::Running;
}

MovementResult EnemyMovement(Enemy& enemy, const Player& player, const World& world) {
	// Calculate trajectory
	int deltaX = player.x - enemy.x;
	int deltaY = player.y - enemy.y;
	
	int stepX = 0, stepY = 0;
	
	if(deltaX > 0)
		stepX += 1;
	else if(deltaX < 0)
		stepX -= 1;
	else if(deltaY > 0)
		stepY += 1;
	else if(deltaY < 0)
		stepY -= 1;
	
	// move enemy
	if((enemy.x + stepX) < 0 || (enemy.x + stepX) >= gridWidth ||
	   (enemy.y + stepY) < 0 || (enemy.y + stepY) >= gridHeight) {
		return MovementResult::OutOfBounds;
	}
	else if(world.tiles[enemy.y + stepY][enemy.x + stepX] !=
			WorldTile::Empty) {
		return MovementResult::Blocked;
	} else if((enemy.x + stepX) == player.x && 
			  (enemy.y + stepY) == player.y) {
		return MovementResult::PlayerCaptured;
	} else {
		enemy.x += stepX;
		enemy.y += stepY;
		return MovementResult::Success;
	}
}

void BuildRenderBuffer(RenderBuffer& buffer, const GameState& currentGameState) {
	for(int row = 0; row < gridHeight; row++)
	{
		for(int col = 0; col < gridWidth; col++)
		{
			switch (currentGameState.world.tiles[row][col])
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
			
			if(row == currentGameState.player.y && col == currentGameState.player.x)
				buffer.tile[row][col] = RenderTile::Player;
			
			for(const Enemy& enemy : currentGameState.enemies)
				if(row == enemy.y && col == enemy.x)
					buffer.tile[row][col] = RenderTile::Enemy;
		}
	}
}

void ResolveWait() {
	return;
}

void Render(const RenderBuffer& buffer) {
	ClearScreen();
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
		case RenderTile::Enemy: std::cout << "x"; break;
		default: std::cout << "Invalid Render State!"; break;
	}
}

MovementResult MovementResolution(Player& player, InputDirection direction, const World& world) {
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
	} else if(world.tiles[targetY][targetX] != WorldTile::Empty) {
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
//End of file.
