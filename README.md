# My mystery game 
This is a 2D game developed in C (developed as a high school short project) using the Raylib library for which the general documentation is already public. 

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
