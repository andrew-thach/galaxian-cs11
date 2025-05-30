![preview](https://upload.wikimedia.org/wikipedia/en/0/09/Galaxian.png)

# Galaxian-CS11
[Galaxian](https://en.wikipedia.org/wiki/Galaxian) is a fixed shooter video game developed and published by Namco for arcades.

This repository hosts starter code for students to build a similar game.

The game is text-based, and relies on [ncurses](https://en.wikipedia.org/wiki/Ncurses), a library that makes it easier to build TUIs (terminal user interfaces).

# Dependencies
Before starting this project, you might need to install the **ncurses** library.
Installation depends on your environment:

### WSL (Ubuntu)
```bash
sudo apt install libncurses-dev
```

### MacOS
Ncurses should already be installed, since this comes with the default MacOS C++ environment that was installed in the beginning of the semester.

# Getting started
Navigate to your projects directory, and clone this repository.
```bash
git clone https://github.com/andrew-thach/galaxian-cs11.git
```

Navigate to the project folder.
```bash
cd galaxian-cs11
```


Compile the sources (.cpp files) and link the **ncurses** library:
```bash
g++ -Wall -pedantic Galaxian.cpp main.cpp -lncurses -o play
```

Run the application.
```bash
./play
```

### Controls
To interact with the game:
- **Left arrow** and **right arrow** to move.
- **Spacebar** to shoot a bullet.
- **q** to quit.

# Project Directions
1. Run the game to see the current state of its implementation.
2. Trace through the code to understand its intended design.
3. Look for the "TODO" comment in the incomplete ```update_game()``` function and implement it.
4. (Optional) Feel free to refactor, add or modify any additional features.

# Note(s)
- When debugging, ```std::cout``` from ```<iostream>``` isn't compatible when the ncurses screen is open. 
You may need to create your own file stream from ```<fstream>``` to create debug logs in order to sanity check certain parts of the game.
- The game is currently implemented for ASCII characters. UTF-8 characters (like emojis) are wider, and messes with the alignment and hitboxes.
