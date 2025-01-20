#include "game.h"
#include "base_server.h"
#include "base_client.h"
#include <stdio.h>
#include <stdlib.h>

void display_leaderboard () {
  FILE * fp = fopen(LEADERBOARD_FILE, "r+b");
  if(fp == NULL) {
    printf("No leaderboard to display yet\n");
    exit(1);
  }
  struct leaderboard_stats player;
  printf("\nLEADERBOARD\n");
  printf("Username%12sWins%4sLosses\n", "", "");
  printf("================================================\n");
  while(fread(&player, sizeof(struct leaderboard_stats), 1, fp) == 1) {
    printf("%-20s%-8d%d\n\n", player.username, player.wins, player.losses);
  }
  fclose(fp);
}
int main(){
    display_leaderboard();
}