## Development Log

### Day 14 - System Separation

#### Goal:

Decompose update function into singular modular systems for ease of repurpose.

#### Algorithm:

- Remove logic control from Update()
- Create:
  - HandlePlayerAction()
  - UpdateEnemies()
  - CheckGameOver()
- Call in order inside Update()

#### Constraints:

- No global state
- All functions take GameState&
- No system does more than one task

#### Completion Criteria:

- Update() becomes a simple orchestrator
- Each system is isolated and readable
- Behavior remains identical
