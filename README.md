# My mystery game 📜✨
This is a 2D game developed in C using the Raylib library for which the general documentation is already public. 

## 🏛️ Plot Overview
You wake up locked inside a mysterious classroom. To break free, you must navigate through 2 magical rooms with hidden objects and secrets inspired by the wizarding world of *Harry Potter*. 

There are no direct clues in the game—your knowledge of the books and movies is the only key to figuring out how to interact with the environment and escape!

## 🛠️ Requirements and Installation
The game was developed on macOS and to compile it it is necessary to have installed the `gcc` compiler and the Raylib library. 

**Command to compile:**
to compile:
```bash
gcc main.c -o gioco -I ./raylib/src -L ./raylib/src -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
  ```

to run:
```bash
./gioco
  ```

## 🎮 Controls
* **A,S,D and W keys**:to move the character
* **R keys**:to collect the objects
* **ESC**: close the game 
