![preview](https://upload.wikimedia.org/wikipedia/en/0/09/Galaxian.png)

# Galaxian-CS11
[Galaxian](https://en.wikipedia.org/wiki/Galaxian) is a fixed shooter video game developed and published by Namco for arcades.

This repository hosts starter code for students to build a similar game.

The game is text-based, and relies on [ncurses](https://en.wikipedia.org/wiki/Ncurses), a library that makes it easier to build TUIs (text based interfaces).

# Getting started
Navigate to your projects directory, and clone this repository.
```bash
git clone https://github.com/andrew-thach/galaxian-cs11.git
```

Compile and link the ncurses library:
```bash
g++ -Wall -pedantic Galaxian.cpp main.cpp -lncurses -o play
```

Run the application.
```bash
./play
```

# Project Directions
1. Trace through the code to understand its intended design.
2. Look for the "TODO" comment in the incomplete ```update_game()``` function and implement it.
3. (Optional) Feel free to add or modify any additional features.

# Note(s)
- When debugging, ```std::cout``` from ```<iostream>``` isn't compatible when the ncurses screen is open. 
You may need to create your own file stream from ```<fstream>``` to create debug logs in order to sanity check certain parts of the game.
- The game is currently implemented for ASCII characters. UTF-8 characters (like emojis) are wider, and messes with the alignment and hitboxes.
