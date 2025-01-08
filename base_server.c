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



int main() {
    signal(SIGINT, sighandler);
    srand(time(NULL));
    int frm[100];
    int to[100];
    int z = 0;
    while (z < 1) {
        printf("\n[server] waiting for client connection\n");
        int from_client = server_setup();
        int to_client;
        server_handshake_half(&to_client, from_client);
        frm[z] = from_client;
        to[z] = to_client;
        z++;
    }
    char buffer[100] = "test2";
    for (int i=0;i<2;i++){
        printf("Wrote too %d for %d\n",to[i],i);
        write(to[i],buffer,100);
    }
    printf("FROMS %d %d\n",frm[0],frm[1]);
    printf("TOS %d, %d\n\n", to[0],to[1]);
    close(frm[0]);
    close(frm[1]);
    close(to[0]);
    close(to[1]);
    return 0;
}
