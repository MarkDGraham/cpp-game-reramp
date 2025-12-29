# Console Game Engine Prototype (C++)

This repository contains a console-based game engine prototype written in C++.
The goal of this project is to demonstrate core engine concepts such as:

- Structured game loop (Input → Update → Render)
- Input intent separation
- Grid-based world logic
- Deterministic player movement
- Clean separation of concerns

## Current Features
- Fixed-timestep game loop
- Enum-based input intent system
- Grid-bounded player movement
- Console rendering

## Tech Stack
- C++17
- Linux (Ubuntu)
- Standard Library only

## Purpose
This project is part of a long-term portfolio focused on transitioning into
a Software Development Engineer role, with emphasis on game engine fundamentals.

## Build & Run
```bash
g++ -std=c++17 src/main.cpp -o game
./game
```

