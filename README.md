# Tower Defense Game (C Project)  

## Overview  
This project is a simplified, turn-based Tower Defense game inspired by "Plants vs. Zombies." The game simulates a battle between a player defending a university from waves of enemy students.

## Features  
- Single-player gameplay against an AI opponent.  
- ASCII-based interface for visualization.  
- Waves of enemies with varying types and characteristics.  
- Multiple types of defense towers with unique abilities.  
- Scalable difficulty levels, from basic functionality to advanced features like graphical interfaces.  

## Project Structure  
The project includes the following key files and folders:  
- `src/` : Source code files for the game logic and mechanics.  
- `include/` : Header files defining the structures and prototypes.  
- `levels/` : Predefined game levels in standardized text files.  
- `README.md` : This file, detailing the project.  
- `dev.pdf` : A detailed report explaining design choices, algorithms, and challenges.  
- `Makefile` : (Optional) To simplify the build process.  

## Compilation and Execution  
### Prerequisites  
- GCC compiler (tested with version 9.4+).  
- A terminal supporting ANSI escape codes (e.g., Unix, macOS, or a configured Windows terminal).  

### Compilation  
Use the following command to compile the project:
```bash
gcc -Wall -g -o tower_defense src/*.c
```

### Running the Game  
Run the compiled executable with:
```bash
./tower_defense [level_file]
```
- Replace `[level_file]` with the path to a game level file (e.g., `levels/level1.txt`).

### Memory Debugging  
Use `valgrind` to ensure proper memory management:
```bash
valgrind ./tower_defense [level_file]
```

## Game Rules  
1. The player places defensive towers on a 7x15 grid before the game starts, limited by available credits.  
2. Enemy students attempt to invade, appearing turn by turn.  
3. Each turn involves:  
   - Enemy spawns and movements.  
   - Towers attacking enemies.  
   - Resolution of interactions.  
4. The game ends when:  
   - The university is breached (loss).  
   - All enemies are defeated (win).  

## Levels  
Levels are defined in plain text files with the following structure:  
1. First line: Total credits available to the player.  
2. Remaining lines: Enemy spawn schedule, in the format:  
   ```plaintext
   [turn_number] [line_number] [enemy_type]
   ```

## Contributions and License  
This project was developed as part of the L2 MIDO C Programming course at Dauphine University (2024-2025). All code must adhere to the academic integrity policies, and unauthorized use of external resources is strictly prohibited.
