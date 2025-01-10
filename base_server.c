#include "pipe_networking.h"
#include <signal.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.h"

void sighandler(int signo)
{
    if (signo == SIGINT)
    {
        remove(WKP);
        exit(0);
    }
}

void write_stats(int wol, char user[500]) {} // for win or lose

int play_game(int frm1, int frm2, int to1, int to2, int who)
{
    struct game_move game_move_array[2];
    // add a for loop with %2 later
    game_move_array[0].ismove = YOUR_TURN;
    game_move_array[1].ismove = OPPONENT_TURN;
    printf("Wrote to %d\n", to1);
    write(to1, &game_move_array[0], GS);
    printf("Wrote to %d\n", to1);
    write(to2, &game_move_array[1], GS);
    struct game_move curr_move;

    while (1)
    {
        read(frm1, &curr_move, GS);
        printf("Server %d got move %d %d \n", who, curr_move.row, curr_move.col);
        write(to2, &curr_move, GS);
        read(frm2, &curr_move, GS);
        printf("Server %d got move %d %d \n", who, curr_move.row, curr_move.col);
        write(to1, &curr_move, GS);
        sleep(1);
        break;
    }

    close(frm1);
    close(frm2);
    close(to1);
    close(to2);
    return 1;
}

int main()
{
    signal(SIGINT, sighandler);
    srand(time(NULL));
    int frm[100];
    int to[100];
    int z = 0;
    int alive[100];
    int alive_stat = 122;
    while (z < 4)
    {
        printf("\n[server] waiting for client connection\n");
        int from_client, to_client;
        from_client = server_handshake(&to_client);
        frm[z] = from_client;
        to[z] = to_client;
        z++;
        alive[z] = alive_stat;
    }

    while (matches <= (z + 1 % 2))
    {
        int q = 0;
        for (int i = 0; i < z; i += 2)
        {
            pid_t pid = fork();
            if (pid == 0)
            {
                q = play_game(frm[i], frm[i + 1], to[i], to[i + 1], 1);
                exit(q + i);
            }
        }
        int status;
        pid_t child_pid;
        alive_stat--;
        z = 0;
        while ((child_pid = wait(&status)) > 0)
        {
            if (WIFEXITED(status))
            {
                int return_value = WEXITSTATUS(status);
                alive[return_value] = alive_stat;
                printf("Child process %d exited with return value: %d\n", child_pid, return_value);
                z++;
            }
            else
            {
                printf("Child process %d did not terminate normally.\n", child_pid);
            }
            int matches = 0;
        }
    }
    return 0;
}
