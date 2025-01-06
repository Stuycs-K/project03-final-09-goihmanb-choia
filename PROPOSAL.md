### Description of Project:
A tic tac toe game with options to play 1v1s or in a tournament-style round. The game also saves leaderboard stats.

---

### How It Will Be Used:
Players will play through the command line. There will be one server started for each game/tournament, and each player will connect through a client to play. The board will be displayed, and the user will enter a row, then column.

---

### Timeline:
- **1/10**: Tic tac toe game between two clients  
- **1/13**: Add sighandler and file data to save a leaderboard of wins  
- **1/17**: Finish tournament style  
- **Extra Features** (post-1/17): Connect 4, save game state / resume games  

---

### Technical Design:
#### Topics from Class:
1. **Memory Allocation**:  
   We will use allocated memory for defining any variables, structs, or arrays needed.  
   
2. **File Handling**:  
   We will work with files to save stats of users who play. For example, when a user wins or loses a game, that stat will be saved. Later, we can read the file to see the top players.  
   
3. **Signals**:  
   - Signals will be used to implement extra features like saving the game state before exiting.  
   - They will also be utilized in the server to handle scenarios where a user disconnects. For example, if a player disconnects mid-game, the server will treat it as a loss, ensuring the game or tournament continues without crashing.  

4. **Pipes**:  
   Pipes will serve as the main method of communication between different players, building on concepts from the pipe networking lab.  

---

### Responsibilities:

#### **Andrew Choi**:
- Work on server-side logic to allow communication for tic tac toe across players.  
- Add the UI to print the tic tac toe board and handle user input.  
- Implement the Tic Tac Toe game algorithm, including win, loss, and tie detection.  

#### **Benjamin Goihman**:
- Handle server-side logic for matchmaking users.  
- Implement server-side logic for progression between matches.  
- Differentiate between 1v1s and tournament modes on the server side.  
- Manage tournament stats and the leaderboard.  

This division balances the workload while keeping roles clear and aligned with team preferences.

---

### Algorithms and Data Structures:
- **Three-Way Handshake**  
- **2D Array** for the board  
- **Algorithm** to detect if a tic tac toe game is tied/won/lost  
- **Tournament Matcher** to handle odd numbers of players  

