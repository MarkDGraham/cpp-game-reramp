## Development Log

### Day 9 - Console Renderer

#### Goal:

Separate simulation logic from rendering by introducing a RenderBuffer layer.

#### Rendering Algorithm:

- main calls BuildRenderBuffer
- BuildRenderBuffer takes in world and player state
  - determines which tile should be displayed at each position
  - updates RenderTile structs with the correct representation
- main calls Render
  - has no access to world or player
  - iterates over RenderTile grid and prints to console

#### Constraints:

- Game logic does not print to console
- Game state is separate from render state
- Renderer does not modify game state
- No gameplay changes introduced

#### Completion Criteria:

- Game logic is fully separated from renderer
- Renderer only depends on RenderBuffer
- No change in visible output compared to previous iteration
- Engine loop remains stable and readable
