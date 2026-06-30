# My mystery game 📜✨
This is a 2D game developed in C using the Raylib library for which the general documentation is already public. 

## 🏛️ Plot Overview
You find yourself inside a classroom where the doors are locked, and the only way to escape is to solve puzzles related to ancient tomes, shadows, and symmetries.

## 🛠️ Requirements and Installation
The game was developed on macOS and to compile it it is necessary to have installed the `gcc` compiler and the Raylib library. 

**Command to compile:**
\`\`\`bash
gcc main.c -o gioco -I ./raylib/src -L ./raylib/src -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
\`\`\`

## 🎮 Controls
* **A,S,D and W keys**:to move the character
* **R keys**:to collect the objects
* **ESC**: close the game 