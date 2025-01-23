PA1 for CPTS 223

Description
This project is a C++ program that implements a matching game where players must match Linux commands with their respective descriptions. The game supports file handling, player management, and includes a custom-built linked list for handling Linux commands.

Features
Menu-driven Interface:
View game rules.
Play the game with randomized command descriptions.
Load and save player profiles.
Add or remove Linux commands.
Linked List: The game uses a custom singly linked list to store and manage Linux commands.
File Handling: Commands are stored in commands.csv, and player profiles are stored in profiles.csv.
Randomized Questions: For each game session, commands are randomly selected to keep the game engaging.
Points System: Players gain or lose points based on their answers, which are saved across sessions.

File Descriptions
Header.h: Contains class declarations for managing the Linux commands and player profiles.
main.cpp: Contains the main menu system and game logic.
Game.cpp: Implements the player profile handling and the game functionality.
commands.csv: Stores the list of Linux commands and their descriptions, which are used in the game.
profiles.csv: Stores player names and scores, allowing players to load their profiles and resume their games.

Author
Melvin Sanare
