## Development Log

### Day 15 - Event Decoupling

#### Goal:

Introduce light weight event system to decouple game rules and engine control. 

#### Algorithm:

- Create EventType
- Create Event struct
- Add vector of events to GameState
- Systems push events
- GameRules cosumes events

#### Constraints:

- No globals
- Events are cleared every frame
- Systems ONLY emit, never decide outcomes

#### Completion Criteria:

- No system directly triggers GameOver
- All outcomes go through event processing
