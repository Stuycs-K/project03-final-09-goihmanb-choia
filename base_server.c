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

void err() {
  printf("%s\n", strerror(errno));
  exit(1);
}
void write_stats(int wol,char user[500]){} //for win or lose

int play_game(int frm1, int frm2, int to1, int to2, int who, int matches){
    struct game_move game_move_array[2];
    game_move_array[0].ismove = YOUR_TURN;
    game_move_array[0].msg_type = O;
    game_move_array[1].ismove = OPPONENT_TURN;
    game_move_array[1].msg_type = X;
    if(write(to1, &game_move_array[0],GS) < 0) err();
    if(write(to2, &game_move_array[1],GS) < 0) err();
    struct game_move curr_move;

    while(1) {
      if(read(frm1, &curr_move, GS) < 0) err();
      if(curr_move.won == MOVE_WIN) {
        printf("Player %d wins!\n", who);
        if(matches == 1) {
          curr_move.won = TOURNAMENT_WIN;
        }
        write(to1, &curr_move, GS);
        curr_move.won = MOVE_LOSE;
        if(write(to2, &curr_move, GS) < 0) err();
        close(to2);
        close(frm2);
        return 0;
      }
      if(write(to2, &curr_move, GS) < 0) err();
      if(read(frm2, &curr_move, GS) < 0) err();
      printf("Server %d got move %d %d \n", who, curr_move.row, curr_move.col);
        if (curr_move.won == MOVE_WIN) {
            printf("Player %d wins!\n", who + 1);
            if(matches == 1) {
              curr_move.won = TOURNAMENT_WIN;
            }
            write(to2, &curr_move, GS);
            curr_move.won = MOVE_LOSE;
            if(write(to1, &curr_move, GS) < 0) err();
            close(to1);
            close(frm1);
            return 1;
        }
      if(write(to1, &curr_move, GS) < 0) err();
    }
    close(frm1);
    close(frm2);
    close(to1);
    close(to2);
    return 0;
}

int main() {
    signal(SIGINT, sighandler);
    srand(time(NULL));
    int frm[100];
    int to[100];
    int player_count = 0;
    int round = 1;
    int *active_players = calloc(100, sizeof(int));
    int alive_state = 0;

    printf("Waiting for players to connect...\n");
    while (player_count < 4) {
        printf("\n[server] waiting for client connection %d/4\n", player_count + 1);
        int from_client, to_client;
        from_client = server_handshake(&to_client);
        frm[player_count] = from_client;
        to[player_count] = to_client;
        active_players[player_count] = alive_state;
        player_count++;
    }

    int players_remaining = player_count;
    printf("Tournament starting with %d players!\n", player_count);

    while (players_remaining > 1) {
        printf("\n=== Round %d ===\n", round);
        int matches = players_remaining / 2;


        for (int i = 0; i < player_count; i++) {
            if (active_players[i] != alive_state) continue;

            int opponent = -1;
            for (int j = i + 1; j < player_count; j++) {
                if (active_players[j] == alive_state) {
                    opponent = j;
                    break;
                }
            }

            if (opponent != -1) {
                int pid = fork();
                if (pid < 0) err();
                if (pid == 0) {
                    int result = play_game(frm[i], frm[opponent], to[i], to[opponent], i + 1, matches);
                    int win_idx = result == 0 ? i : opponent;
                    exit(win_idx);
                }
                active_players[i] = -1;
                active_players[opponent] = -1;
            }
        }
        alive_state++;

        for (int i = 0; i < matches; i++) {
            int status;
            pid_t wpid = wait(&status);
            if (WIFEXITED(status)) {
                int winner_idx = WEXITSTATUS(status);
                active_players[winner_idx] = alive_state;
                players_remaining--;
            }
        }

        round++;
        printf("Players remaining %d\n", players_remaining);
    }

    for (int i = 0; i < player_count; i++) {
        if (active_players[i]) {
            printf("Player %d wins the tournament!\n", i + 1);
            break;
        }
    }

    free(active_players);
    return 0;
}
