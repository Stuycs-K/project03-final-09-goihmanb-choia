# Dev Log:

This document must be updated daily by EACH group member.

## Andrew Choi

### 2024-01-06 - Work on README.md and PROPOSAL.md
Added project description to README.md and filled out project intentions, intended usage, and intended pacing for PROPOSAL.md

### 2024-01-07 - Headers and makefile
Worked on function headers and added the .h files - 15 minutes
Created makefile - 15 minutes

### 2024-01-08 - Figure out server and subserver configuration
Worked on planning out the communication for the tournament style game with the main server and subserver - 40 mins

### 2024-01-09 - Seever client interaction
Enabled communication between the two clients through a server, where a client knows if it is it's turn, then sends a move to the server which sends the move to the other client.

### 2024-01-10 - Server client constant communication
Enabled the clients to constantly send moves to each other until one exits through a main server - 20 mins.
Worked on sending game moves and storing and displaying the board for each client.

### 2024-01-10 - Client gameplay
Clients can now take user input to send moves to the other client.
Clients also display the move, now need to add game logic and index checking
Also need to add exit code for winner

### 2024-01-13 - Game logic and sending wins to server
Clients know if they've won, and will send that message to the server
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

## Benjamin Goihman

### 2025-01-06 - Work on PROPOSAL.md
Refreshed MD on proposal.md, adding clarifaciton and more specfic from the orginal google doc. 5 minutes
added server code from my lab, as base for forking - 10 min

### 2025-01-07 - Work on skeleton code
added client skeleton code and game skeleton - 20 min
added correct imports and other needed funcs for base server and client - 8 min

### 2025-01-08 - Work tic tac toe formatting
added formattig and prinint of the tictactoe board - 10 min

### 2025-01-09 - Rember to add


### 2025-01-10 - Worked on forking server
allowed for multiple clients to play at once on subservers and then subserver with exit code return winner

### 2025-01-11 - Worked on forking server
First attempt at matchmaking the players, inclduing routing users to play against each other.
Fix keeping track of alive players and use new method for that.
