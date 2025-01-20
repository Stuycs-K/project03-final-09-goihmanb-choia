# Dev Log:

This document must be updated daily by EACH group member.

## Andrew Choi

### 2024-01-06 - Work on README.md and PROPOSAL.md
Added project description to README.md and filled out project intentions, intended usage, and intended pacing for PROPOSAL.md - 10 mins

### 2024-01-07 - Headers and makefile
Worked on function headers and added the .h files - 15 minutes
Created makefile - 15 minutes

### 2024-01-08 - Figure out server and subserver configuration
Worked on planning out the communication for the tournament style game with the main server and sub server - 40 mins

### 2024-01-09 - Server client interaction
Enabled communication between the two clients through a server, where a client knows if it is it's turn, then sends a move to the server which sends the move to the other client. - 30 minutes

### 2024-01-10 - Server client constant communication
Enabled the clients to constantly send moves to each other until one exits through a main server - 20 mins.
Worked on sending game moves and storing and displaying the board for each client. - 20 mins

### 2024-01-10 - Client gameplay
Clients can now take user input to send moves to the other client. 15 mins
Clients also display the move, now need to add game logic and index checking - 10 mins
Also need to add exit code for winner

### 2024-01-13 - Game logic and sending wins to server
Clients know if they've won, and will send that message to the server - 10 mins
When the server gets this message, it prints which player wins and attempts to match them up for the next round. - 30 mins

### 2024-01-14 - Bounds checking for game and telling client if they won or lost
Clients know if they win or lose or draw, now they can exit or rematch according to that. -15 mins
Game logic and trying to debug client server tournament second round seg fault - 40 mins

### 2024-01-15 - Tournament exiting
Clients now have a tournament_win variable, so they know if they win the tournament or just game - 30 mins
Fixed the tournament style, now need to fix if not 8 players and have users enter their name - 20 mins
WORK ON:
Work with a non-power of 2 players
Ties

### 2024-01-16 - Cleaning up and fixing draws
Fixed all the .h headers, cleaned up some code - remove some print statements, add some comments. - 15 mins
Draws now rematch - 15 mins
Group ID 7

### 2024-01-17 - Working on leaderboard
Created a leaderboard system that writes to a local file, but it double counts some losses - 40 mins.

### 2024-01-18 - Fixed leaderboard, added server handling when clients exit, and fixed draws with multiple players
Fixed the leaderboard to keep track of stats. (20 mins)
Added error handling when clients exit with read/write in server, and lets the other player win. (90 mins)
Fixed draws with multiple players so that tournament matchmaking works (30 mins)

### 2024-01-20 - Cleaning up and editing readme
Cleaning up code and fixing print statements, adding some colors and changing server to get input for number of players - 15 mins

## Benjamin Goihman

### 2025-01-06 - Work on PROPOSAL.md
Refreshed MD on proposal.md, adding clarifaciton and more specfic from the orginal google doc. 5 minutes
added server code from my lab, as base for forking - 10 min

### 2025-01-07 - Work on skeleton code
added client skeleton code and game skeleton - 20 min
added correct imports and other needed funcs for base server and client - 8 min

### 2025-01-08 - Work tic tac toe formatting
added formattig and prinint of the tictactoe board - 10 min

### 2025-01-09 - Print board and client tracking
Worked on fixing tracking the cleints - 5 min
Added board pritning - 10 min

### 2025-01-10 - Worked on forking server
allowed for multiple clients to play at once on subservers and then subserver with exit code return winner  - 40 min


### 2025-01-12 - Matchmaking
Set up matchmaking the players (server side), inclduing routing users to play against each other. - 40 min
Fix keeping track of alive players and use new method for that. - 10 min
Continue working on matchmaking players and work on end game conditions - 20 min

### 2025-01-13
Sick ):

### 2025-01-14 - Usernames
Add username to clinets - 5 min
Fix column printing - 5 min

### 2025-01-15 - Usernames
add sending clients username to server - 20 min

### 2025-01-16 - Byes
Add byes when non even amount of players - 40 min

### 2025-01-17 - Byes and Ties
Work on adding byes and fix loop for byes occurs - 40 min
Fix client side loop as well as server side, allow for players to skip game loop when on bye - 10 min
Work on limiting max amount of ties - 30 min

### 2025-01-18 - Keep track of players
Add a print statemnt for who you after each round - 3 min
Refactor code - 3 min

### 2025-01-20 - Fix errors
Fix compile error in client - 2 min
Add leaderboard make target - 5 min
