## Development Log

### Day 6 - Console Renderer

#### Goal:

Render the world grid with a player overlay without mutating the game state.

#### Rendering Algorithm:

- Iterate rows, then columns
- Overlay player position
- delegate symbol printing to helper logic

#### Constraints:

- World grid is read only
- player position stored separately
- Renderer has no side effects

#### Completion Criteria:

- Full grid renders every frame
- Player appears correctly
- No logic duplication
