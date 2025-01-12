#include "pipe_networking.h"
#include "game.h"
#include "base_client.h"

void game_loop(int to_server, int from_server, pid_t my_pid) {
  int board[3][3];
  for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 3; j++) {
        board[i][j] = 0;
    }
  }
  char display [1000];
  struct game_move move;
  if(read(from_server,&move,GS)<=0){
          printf("%s",strerror(errno));
  }
  int my_character = move.msg_type;
  int opp_character = (my_character == O) ? X : O;
  if (move.ismove == YOUR_TURN) {
    write_to_server(move, board, to_server, my_character);
  }
  while(1) {
    if(read(from_server, &move, GS) < 0) {
      printf("%s\n", strerror(errno));
    }
    board[move.row][move.col] = opp_character;
    // printf("Received move from client, %d %d\n", move.row, move.col);
    format_brd(board, display);
    write_to_server(move, board, to_server, my_character);
    // printf("Sending move to client, %d %d\n", move.row, move.col);
  }
}

char * format_brd(int board[3][3], char ret[1000]){
    int index = 0;
    for(int i = 0; i<3;i++){
        for(int j = 0; j<3;j++){
            if(board[i][j]==X){
                ret[index++] = 'X'; // To keep track of wehre
            }
            else if (board[i][j]==O){
                ret[index++] = 'O';
            }
            else {
                ret[index++]=' ';
            }
            if(j!=2){
              ret[index++]='|';
            }
        }
        if(i!=2){
            ret[index++] = '\n';
            ret[index++]='-';
            ret[index++]='-';
            ret[index++]='-';
            ret[index++]='-';
            ret[index++]='-';
            ret[index++]='-';
            ret[index++]='-';
            ret[index++] = '\n';

        }
    }
    ret[index++] = '\n';
    ret[index] = '\0';
    printf("%s", ret);
    return ret;
}

void write_to_server(struct game_move move, int (*board)[3], int to_server, int my_character) {
  char rowbuff [10];
  char colbuff [10];
  char *endptr;
  printf("Enter the row, from 1 to 3: \n");
  fgets(rowbuff, sizeof(rowbuff), stdin);
  printf("Enter the column, from 1 to 3: \n");
  fgets(colbuff, sizeof(colbuff), stdin);
  int r = strtol(rowbuff, &endptr, 10);
  int c = strtol(colbuff, &endptr, 10);
  move.row = r - 1;
  move.col = c - 1;
  board[r - 1][c - 1] = my_character;
  write(to_server, &move, GS);
}
int main() {
    int to_server;
    int from_server;
    pid_t my_pid = getpid();
    from_server = client_handshake(&to_server);
    printf("From server %d\n",from_server);
    game_loop(to_server, from_server, my_pid);
    int board[3][3] = {
        {1,0,1},
        {1,0,-1},
        {1,1,1}
    };
    char ret[1000];
    printf("%s",format_brd(board,ret));
    return 0;
}


int checkforcond(int plyr, int board[3][3]){
    //Return 1 if plyr won, 0 if continue playing, -1 if lost, -2 if tied. To be called after plyr made thier move
}


char * display_leaderboard (FILE * f) {} // Return the string for the leaderboard.
