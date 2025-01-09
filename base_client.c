#include "pipe_networking.h"
#include "game.h"

void game_loop(int to_server, int from_server, pid_t my_pid) {
    struct game_move move;

    while(1) {

        // Gets the move from user, then cehck for win/tie,sends move, gets reponse and llops

    }
}

char * format_brd(int board[3][3], char ret[1000]){
    int index = 0;
    for(int i = 0; i<3;i++){
        for(int j = 0; j<3;j++){
            if(board[i][j]==X){
                ret[index++] = 'X'; // To keep track of wehre 
            }
            if (board[i][j]==O){
                ret[index++] = 'O';
            }
            else{
                ret[index++]=' ';
            }
            if(j!=2){ret[index++]='|';}
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
            ret[index++]='-';
            ret[index++] = '\n';

        }
    }
            ret[index++] = '\n';

    return ret;
}
int main() {
    int to_server;
    int from_server;
    pid_t my_pid = getpid();
    from_server = client_handshake(&to_server);
    printf("In client %d\n",to_server);
    // game_loop(to_server, from_server, my_pid);
    char buffer[100];
    if(read(from_server,buffer,100)<=0){
            printf("%s",strerror(errno));
    }
    printf("%s\n",buffer);
    return 0;
    int board[3][3] = {
        {1,0,1},
        {1,0,-1},
        {1,1,1}
    };
    char ret[1000];
    printf("%s",format_brd(board,ret));
}


int checkforcond(int plyr, int board[3][3]){
    //Return 1 if plyr won, 0 if continue playing, -1 if lost, -2 if tied. To be called after plyr made thier move
}


char * display_leaderboard (FILE * f) {} // Return the string for the leaderboard.
