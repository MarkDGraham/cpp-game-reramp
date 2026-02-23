## Development Log

### Day 8 - Wait Action

#### Goal:

Introduce a new action into the designed system that consumes a turn inside the game loop.

#### Algorithm:

- Expand ActionIntent enum
  - Add wait type
- Process input update
  - Add 'e' key input
- Enhance Update function
  - add switch case
  - add move case
  - add wait case
  - call WaitResolution
- Implement WaitResolution Function

#### Constraints:

- No state mutation in ProcessInput except setting the intent.
- All action logic goes through the resolution layer (MovementResolution, ResolveWait).
- Maintain separation of concerns: Update only routes, resolutions handle action details.

#### Completion Criteria:

- Intent_Wait implemented
- Update routes actions cleanly
- Movement system unchanged
- Input key 'e' triggers wait action
- Test cases pass
- Code remains modular for future expansion
