# RESET - A Text Adventure Game

## Project Description

RESET is a C++ text adventure game where the player explores an abandoned building and tries to escape. The main feature of the game is the reset system. When the player dies, they return to the beginning, but they keep important memories from previous attempts.

The player must learn from mistakes, remember clues, avoid traps, and use the information from past deaths to reach the final escape.

## How to Compile and Run

From the main project folder, compile the program with:

g++ src/main.cpp src/GameEngine.cpp src/Scene.cpp src/Choice.cpp src/PlayerState.cpp src/ResetManager.cpp -o reset

Run the program with:

./reset

## Features

- Text-based adventure gameplay
- Multiple rooms and paths
- Reset system after death
- Memory log that keeps important clues
- Temporary progress that resets after death
- Several death paths and traps

## Data Structures Used

### map

The game uses a map<int, Scene> to store all scenes by ID. This makes it easier to move between rooms using scene numbers.

### vector

The game uses vector<Choice> to store the choices inside each scene. It also uses vector<string> to store the player's memory log.

### stack

The game uses a stack<int> for scene history. This can be used to track previous scenes visited by the player.

### string

The game uses strings for scene descriptions, player choices, memory text, and messages shown to the player.

## Algorithms Used

### Scene Navigation Algorithm

The program tracks the current scene ID and uses the player's choice to move to the next scene.

### Reset Memory Algorithm

When the player dies, temporary progress is reset, but important memories are kept in the memory log.

### Action Validation Algorithm

Before moving the player to certain rooms, the program checks if the player has the required memory or temporary state. 

Example: The player must know the door code before safely opening the locked door, and the ventilation must be active before entering the gas room.

## Contributor

Esteban Pereira das Neves Siburo