#include "pipe_networking.h"
#include "game.h"

void game_loop(int to_server, int from_server, pid_t my_pid) {
    struct game_move move;

    while(1) {

        // Gets the move from user, then cehck for win/tie,sends move, gets reponse and llops

    }
}

int main() {
    int to_server;
    int from_server;
    pid_t my_pid = getpid();
    from_server = client_handshake(&to_server);
<<<<<<< HEAD
    printf("In server %d\n",to_server);
=======
    printf("From server %d\n",from_server);
>>>>>>> f0792810dfddd0325cd3b77388d1fd313418f53f
    // game_loop(to_server, from_server, my_pid);
    char buffer[100];
    if(read(from_server,buffer,100)<=0){
            printf("%s",strerror(errno));
    }
    printf("%s\n",buffer);
    return 0;
}


int checkforcond(int plyr, int board[3][3]){
    //Return 1 if plyr won, 0 if continue playing, -1 if lost, -2 if tied. To be called after plyr made thier move
}

char * format_brd(int board[3][3]){
    //Prints board nicely with X's and 0's
}

char * display_leaderboard (FILE * f) {} // Return the string for the leaderboard.
