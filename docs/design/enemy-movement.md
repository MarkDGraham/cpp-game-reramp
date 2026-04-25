## Development Log

### Day 16 - Enemy Movement

#### Goal:

Refactor enemy movement into a scored decision system while eliminating 
duplicated movement logic.

#### Algorithm:

- Enumerate all possible directions
- Convert each direction into a condidate position
- Validate the move using a shared movement rule system
- Score valid moves using the movement cost and heuristic distance
- Select the best candidate
- Apply movement
- Emit event if player is captured

#### Constraints:

- No duplication of movement rules (this is your biggest issue right now)
- Enemy system should not introduce new “hidden logic paths”
- No direct GameOver mutation (must go through events)

#### Completion Criteria:

- Must integrate into UpdateEnemies
- Must respect GameState as source of truth
- Must not break player movement behavior
