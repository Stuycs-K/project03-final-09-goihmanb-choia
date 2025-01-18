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

//for win or lose
void write_stats(int wol, char username[500]){
  FILE * fp = fopen(LEADERBOARD_FILE, "r+b");
  if(fp == NULL) fp = fopen(LEADERBOARD_FILE, "w+b");
  struct leaderboard_stats curr_player;
  int found = 0;
  while(fread(&curr_player, sizeof(struct leaderboard_stats), 1, fp) == 1) {
    if(strcmp(username, curr_player.username) == 0) {
      if(wol == TOURNAMENT_WIN) curr_player.wins++;
      else curr_player.losses++;
      fseek(fp, -sizeof(struct leaderboard_stats), SEEK_CUR);
      fwrite(&curr_player, sizeof(struct leaderboard_stats), 1, fp);
      printf("Adding to a new player in leaderboard %s wins: %d losses: %d\n", username, curr_player.wins, curr_player.losses);
      found = 1;
      break;
    }
  }
  if(found == 0) {
    strncpy(curr_player.username, username, 499);
    curr_player.username[499] = '\0';
    if(wol == TOURNAMENT_WIN) curr_player.wins++;
    else curr_player.losses++;
    printf("Creating a new player in leaderboard %s wins: %d losses: %d\n", username, curr_player.wins, curr_player.losses);
    fwrite(&curr_player, sizeof(struct leaderboard_stats), 1, fp);
  }
  fclose(fp);
}

int play_game(int frm1, int frm2, int to1, int to2, int p1_ind, int p2_ind, int matches, char usernames[100][500]){
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
        if(matches == 1) {
          curr_move.won = TOURNAMENT_WIN;
          write_stats(TOURNAMENT_WIN, usernames[p1_ind]);
        }
        write_stats(TOURNAMENT_LOSE, usernames[p2_ind]);
        write(to1, &curr_move, GS);
        curr_move.won = MOVE_LOSE;
        if(write(to2, &curr_move, GS) < 0) err();
        close(to2);
        close(frm2);
        return 0;
      }
      if(write(to2, &curr_move, GS) < 0) err();
      if(read(frm2, &curr_move, GS) < 0) err();
        if (curr_move.won == MOVE_WIN) {
            if(matches == 1) {
              curr_move.won = TOURNAMENT_WIN;
              write_stats(TOURNAMENT_WIN, usernames[p2_ind]);
            }
            write_stats(TOURNAMENT_LOSE, usernames[p1_ind]);
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


void set_random_index(int ary[], int n, int max) {
    for(int i = 0; i < n; i++) {
        int num = rand() % max;
        int exists = 0;
        for(int j = 0; j < i; j++) {
            if(ary[j] == num) {
                exists = 1;
                break;
            }
        }
        if(exists) {
            i--;
        } else {
            ary[i] = num;
        }
    }
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
    int max_players = 2;
    char usernames[100][500];
    int byes[9] = {
      0, 0, 0, 1, 0, 3, 2, 1, 0
    };
    printf("Waiting for players to connect...\n");
    while (player_count < max_players) {
        printf("\n[server] waiting for client connection %d/4\n", player_count + 1);
        int from_client, to_client;
        from_client = server_handshake(&to_client);
        frm[player_count] = from_client;
        to[player_count] = to_client;
        active_players[player_count] = alive_state;
        player_count++;
    }

    for (int i = 0; i < max_players; i++){
        read(frm[i],usernames[i],500);
    }
    printf("The names are\n");
    for (int i = 0; i < max_players; i++){
        printf("User %d name is %s\n", i,usernames[i]);
    }

    int players_remaining = player_count;
    printf("Tournament starting with %d players!\n", player_count);

    while (players_remaining > 1) {
        printf("\n=== Round %d ===\n", round);
        int matches = (players_remaining+1) / 2;
        int skips[byes[player_count]];
        if (round == 1){
            set_random_index(skips,byes[player_count],player_count);
            for (int i = 0; i < byes[player_count]; i++){
                active_players[skips[i]] = -11;
            }

            int bye = BYE;
            int norm = 111;
            for (int j = 0; j < player_count; j++) {
                 if (active_players[j] == -11) {
                    write(to[j], &bye, sizeof(int));
                }
                else{
                    write(to[j], &norm, sizeof(int));
                }
        }}
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
                    int result = play_game(frm[i], frm[opponent], to[i], to[opponent], i, opponent, matches, usernames);
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
        if (round==1){
            for (int i = 0; i < byes[player_count]; i++){
                active_players[skips[i]] = alive_state;
                players_remaining++;
            }
        }
        round++;
        printf("Players remaining %d\n", players_remaining);
    }

    for (int i = 0; i < player_count; i++) {
        if (active_players[i]) {
            printf("Player %s wins the tournament!\n", usernames[i]);
            break;
        }
    }

    free(active_players);
    return 0;
}
