## Development Log

### Day 13 - GameState

#### Goal:

Eliminate bloated parameter passing into a centeralized data cluster.

#### Algorithm:

- create a struct that encapulates engine data
- pass engine data object to as a single parameter to functions.

#### Constraints:

- Reduce parameter lists for functions
- Retain same behavior

#### Completion Criteria:

- All major functions use GameState
- No multi-parameter passing for core systems
- Program runs exactly the same
- Clean compile, no warnings
