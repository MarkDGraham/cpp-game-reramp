## Development Log

### Day 7 - Action System

#### Goal:

Intoduce an action resolution layer that converts input intent into validated player actions, ensuring movement and gameplay logic are no longer owned by the input system.

#### Rendering Algorithm:

- ProcessInput captures raw user input and translates it into an InputIntent
  - Sets ActionIntent (e.g., Move)
  - Sets Direction (Up, Down, Left, Right)
- Update passes the current InputIntent to the Action System
- MovementResolver evaluates the intent:
  - Computes target position based on direction
  - Queries the world for tile validity
- If movement is valid:
  - Player position is updated
- If movement is invalid:
  - Player position remains unchanged
- ActionIntent is reset to *none* after resolution

#### Constraints:

- ProcessInput must not:
  - Move the player
  - Query the world
  - Perform collision checks
- Player must only store state (position), not logic
- World must not own player movement logic
- All movement validation must live in a single resolver
- Renderer must remain unaware of action or movement logic
- Input intent must be cleared every frame after processing

#### Completion Criteria:

- Player movement is driven exclusively by the Action System
- Input system only produces intent, never side effects
- Invalid movement attempts do not modify player state
- Renderer continues to function without modification
- Action system is extensible for future actions (e.g., attack, interact)
- Code compiles cleanly with no duplicated movement logic
