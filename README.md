# C Pong

A classic Pong game implemented in pure C.

## Features

- Player vs CPU or Player vs Player modes
- Customizable colors for paddles and ball
- Multiple difficulty levels for CPU opponent
- Score tracking

## Dependencies

- libyaml
- json-c

## Building and Running

### Using CMake

```bash
mkdir build
cd build
cmake ..
make
./pong
```

### Using Makefile

```bash
make
make run
```

## Controls

### Menu Controls

- Up/Down: Navigate menu
- Enter: Select option

### Game Controls

- Player 1: W (up), S (down)
- Player 2: Up Arrow (up), Down Arrow (down)
- P: Pause game
- ESC: Return to menu

### Settings Controls

- Up/Down: Navigate settings
- Left/Right: Change setting value
- Enter: Confirm and return to menu
- ESC: Return to menu without saving

## Project Structure

- `src/`: Source code
  - `game/`: Game logic
  - `gui/`: Graphics and UI handling
  - `config/`: Configuration management
- `pkg/`: Resources
  - `fonts/`: Game fonts
  - `config.yaml`: Game configuration
  - `scores.json`: High scores
