#include "pipe_networking.h"
#include <signal.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void sighandler(int signo) {
    if (signo == SIGINT) {
        remove(WKP);
        exit(0);
    }
}

void write_stats(int wol,char user[500]){} //for win or lose

int check_board(int board [][]) {} // Check to see if the game is over (3 in a row)

char * get_display(int board [][]) {} // Format the board into a string to display to the user.

char * display_leaderboard (FILE * f) {} // Return the string for the leaderboard.


int main() {
    signal(SIGINT, sighandler);
    srand(time(NULL));

    while (1) {
        printf("\n[server] waiting for client connection\n");
        mkfifo(WKP, 0644);
        int from_client = server_setup();
        
        int f = fork();
        if (f > 0) {
            close(from_client);
            continue;
        }
        else if (f == 0) {
            int to_client;
            if (server_handshake_half(&to_client, from_client) != -1) {
                while (1) {
                    int random_num = rand() % 101;
                    printf("[subserver %d] sending: %d\n", getpid(), random_num);
                    if (write(to_client, &random_num, sizeof(int)) == -1) {
                        printf("[subserver %d] client disconnected\n", getpid());
                        break;
                    }
                    sleep(1);
                }
            }
            close(from_client);
            close(to_client);
            return 0;
        }
    }
    return 0;
}