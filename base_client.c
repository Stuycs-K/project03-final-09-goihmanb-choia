#include "pipe_networking.h"
#include "game.h"
#include "base_client.h"

char username[500];

int status_check(int status) {
  if(status == MOVE_LOSE) {
    printf("I lost, exiting\n");
    return MOVE_LOSE;
  }
  if(status == MOVE_TIE) {
    printf("Tie, rematching\n");
    return MOVE_TIE;
  }
  if(status == TOURNAMENT_WIN) {
    printf("I win everything!!\n");
    return TOURNAMENT_WIN;
  }
  if(status == MOVE_WIN) {
    printf("I win\n");
    return MOVE_WIN;
  }
  return MOVE_REGULAR;
}

int game_loop(int to_server, int from_server, pid_t my_pid) {
  int board[3][3];
  for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 3; j++) board[i][j] = 0;
  }
  char display [1000];
  struct game_move move;
  if(read(from_server,&move,GS)<0) printf("%s",strerror(errno));

  int my_character = move.msg_type;
  int opp_character = (my_character == O) ? X : O;
  if (move.ismove == YOUR_TURN) write_to_server(move, board, to_server, my_character);

  while(1) {
    if(read(from_server, &move, GS) < 0) printf("%s\n", strerror(errno));
    int status = status_check(move.won);
    if(status != MOVE_REGULAR) return status;
    board[move.row][move.col] = opp_character;
    format_brd(board, display);
    write_to_server(move, board, to_server, my_character);
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
            ret[index++] = '\n';

        }
    }
    ret[index++] = '\n';
    ret[index] = '\0';
    printf("%s", ret);
    return ret;
}

int write_to_server(struct game_move move, int (*board)[3], int to_server, int my_character) {
  char rowbuff [10];
  char colbuff [10];
  char *endptr;
  int r, c;
  while(1) {
    printf("Enter the row, from 1 to 3: \n");
    scanf("%d", &r);
    printf("Enter the column, from 1 to 3: \n");
    scanf("%d", &c);
    if(r < 1 || r > 3 || c < 1 || c > 3) {
      printf("Invalid index\n");
      continue;
    }
    if(board[r-1][c-1] != 0) {
      printf("Space is occupied\n");
      continue;
    }
    break;
  }
  move.row = r - 1;
  move.col = c - 1;
  board[r - 1][c - 1] = my_character;
  move.won = checkforcond(my_character, board, move.row, move.col);
  if(write(to_server, &move, GS) < 0) printf("err writing to serv %s\n", strerror(errno));
  return move.won;
}

int main() {
    int to_server;
    int from_server;
    pid_t my_pid = getpid();
    from_server = client_handshake(&to_server);
    printf("From server %d\n",from_server);
    while(1) {
      int status = game_loop(to_server, from_server, my_pid);
      if(status == MOVE_LOSE || status == TOURNAMENT_WIN) {
        close(to_server);
        close(from_server);
        break;
      }
      printf("Finished a round\n");
    }
    return 0;
}

//Return 1 if plyr won, 0 if continue playing, -2 if tied. To be called after plyr made thier move
int checkforcond(int plyr, int board[3][3], int row, int col){
  int vert_check = 1;
  int horizontal_check = 1;
  for(int c = 0; c < 3; c++) {
    if(board[row][c] != plyr) {
        horizontal_check = 0;
        break;
    }
  }

  for(int r = 0; r < 3; r++) {
    if(board[r][col] != plyr) {
        vert_check = 0;
        break;
    }
  }
  if(vert_check || horizontal_check) return MOVE_WIN;

  if(board[0][0] == plyr && board[1][1] == plyr && board[2][2] == plyr) return MOVE_WIN;
  if(board[2][0] == plyr && board[1][1] == plyr && board[0][2] == plyr) return MOVE_WIN;

  // check for draw
  int isdraw = 1;
  for (int r = 0; r < 3; r++) {
    for(int c = 0; c < 3; c++) if(board[r][c] == 0) isdraw = 0;
  }
  if(isdraw) return MOVE_TIE;

  return MOVE_REGULAR;
}


char * display_leaderboard (FILE * f) {} // Return the string for the leaderboard.
