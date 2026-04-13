## Development Log

### Day 12 - World System

#### Goal:

Encapsulate world data into a dedicated World system and remove the global worldGrid dependency so all gameplay and rendering systems receive world state explicitly.

#### Algorithm:

- main creates World instance
- main passes World into Update
- Update passes World into gameplay systems
- main passes World into BuildRenderBuffer
- BuildRenderBuffer reads world tiles to populate RenderBuffer

#### Constraints:

- No global world state
- Systems must receive World explicitly
- Rendering does not modify world data
- Gameplay systems must not access world through globals

#### Completion Criteria:

- worldGrid is moved into a World struct
- Global worldGrid is removed
- All systems receive World through parameters
- Game behavior remains unchanged
