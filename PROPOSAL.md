# Final Project Proposal

## Group Members:

Andrew Choi, Benjamin Goihman

# Intentions:

A tic tac toe game, with options to play 1v1’s or in a tournament style round, that also saves leaderboard stats

# Intended usage:

Players will play through the command line, there will be one server started for each game/tournament, then each player will connect through a client and play. The board will be displayed, and the user will enter a row, then column.

# Technical Details:

Topics from class:


We will use allocating memory for defining any variables, structs or arrays we need to use.

We will work with files to save stats of users who play meaning when a user wins or loses a game we can save that stat and then later on we can read the file to see top players.

Signals - When we implement extra features like saving the game state, signals will be used to save the game state before exiting. They will also be utilized in the server to handle scenarios where a user disconnects. For example, if a player disconnects mid-game, the server will treat it as if they lost, ensuring the game or tournament continues without crashing.

Pipes - this will be the main method of communication between the different players, we will be working off the pipe networking lab

Algorithms and / data structures:


We will be using the three way handshake

2d array for the board

Algorithm to detect if tic tac toe game is tied/won/lost

Tournament matcher and deal with odd amount of players


# Intended pacing:

Tic tac toe game between two clients 1/10
Add sighandler and file data to save a leaderboard of wins1/13
Finish tournament style 1/17
Add extra features - save game state / resume games
