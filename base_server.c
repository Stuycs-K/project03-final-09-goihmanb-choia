#include "pipe_networking.h"
#include <signal.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.h"

void sighandler(int signo) {
    if (signo == SIGINT) {
        remove(WKP);
        exit(0);
    }
}

void write_stats(int wol,char user[500]){} //for win or lose



int main() {
    signal(SIGINT, sighandler);
    srand(time(NULL));
    int frm[100];
    int to[100];
    int z = 0;
    while (z < 2) {
        printf("\n[server] waiting for client connection\n");
        int from_client, to_client;
        from_client = server_handshake(&to_client);
        frm[z] = from_client;
        to[z] = to_client;
        z++;
    }
    struct game_move game_move_array[2];
    // add a for loop with %2 later
    game_move_array[0].ismove = YOUR_TURN;
    game_move_array[1].ismove = OPPONENT_TURN;
    for (int i=0;i<2;i++){
        printf("Wrote to %d\n",to[i]);
        write(to[i], &game_move_array[i],GS);
    }
    struct game_move curr_move;
    while(1) {
      read(frm[0], &curr_move, GS);
      printf("Server got move %d %d \n", curr_move.row, curr_move.col);
      write(to[1], &curr_move, GS);
      read(frm[1], &curr_move, GS);
      printf("Server got move %d %d \n", curr_move.row, curr_move.col);
      write(to[0], &curr_move, GS);
      sleep(1);
    }
    // printf("FROMS %d %d\n",frm[0],frm[1]);
    // printf("TOS %d, %d\n\n", to[0],to[1]);
    close(frm[0]);
    close(frm[1]);
    close(to[0]);
    close(to[1]);
    return 0;
}
