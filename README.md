# Dau Invaders 🎮

Tower Defense game implemented in C for the Université Paris Dauphine - PSL Programming Course

## 📝 Description

Dau Invaders is a terminal-based Tower Defense game where players strategically place towers to defend against waves of students. The project demonstrates advanced C programming techniques, including dynamic memory management, data structures, and game logic implementation.

## ✨ Features

- Multiple tower and enemy types
- Strategic tower placement and upgrades
- Custom wave generation
- Save and load game functionality
- Scoring system

## 🛠 Prerequisites

- GCC Compiler
- Unix-like operating system (Linux/macOS)

## 🚀 Installation

1. Clone the repository:
```bash
git clone https://github.com/EliotCassidy/TowerDefense.git
cd TowerDefense
```

2. Compile the project:
```bash
gcc *.c -o dauInvaders -lm -Wall
```

## 🎮 How to Play

1. Ensure you have a `niveau.txt` file in the project directory
2. Run the game:
```bash
./dauInvaders
```

3. Game Modes:
- Single wave mode
- Load saved game

## 🌐 Wave Generator

Create custom game waves using the online tool:
[Wave Generation Tool](https://eliotcassidy.github.io/TowerDefense)

## 📋 Project Structure

- `game.c`: Main game loop and high-level functions
- `meca.c`: Game mechanics implementation
- `ecriture.c`: Display and menu rendering
- `lecture.c`: File reading and game state initialization
- `utils.c`: Utility functions
- `fichier.c`: Save and ranking management

## 👥 Authors

- Eliot Cassidy
- Nicolas de Pellegars

## 📄 License

[To be determined]

## 🙏 Acknowledgments

- Emmanuel Lazard (Course Instructor)
- Ariane Ravier (Teaching Assistant)
- Université Paris Dauphine - PSL


## 🐛 Known Issues

- No infinite game mode (currently in development)
- Limited to terminal-based gameplay

## 🤝 Contributing

Contributions are welcome! Please feel free to submit a Pull Request.


## 🔍 Technical Details

The project showcases:
- Advanced memory management
- Dynamic data structures
- Complex game logic implementation
- File I/O operations
- Input validation techniques
