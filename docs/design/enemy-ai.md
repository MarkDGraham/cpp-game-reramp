## Development Log

### Day 10 - Enemy AI

#### Goal:

Add basic enemy functionality while keeping game logic separate from render logic.

#### Algorithm:

- Define Enemy struct
- Initialize enemy list
- Extend renderTiles enum for enemy
- Update BuildRenderBuffer() to include enemies
- Implement enemy movement logic
- Update game loop to process enemy updates
- Handle collisions (optional placeholder)


#### Constraints:

- Game logic does not render directly
- Player and enemy logic separated
- Render only draws from RenderBuffer

#### Completion Criteria:

- Enemies appear correctly on the console
- Enemy movement is resolved independently of player
- No world or player logic directly prints to console
