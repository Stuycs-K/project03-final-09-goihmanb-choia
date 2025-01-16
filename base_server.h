#ifndef BASE_SERVER_H
#define BASE_SERVER_H
void write_stats(int wol,char user[500]);
void err();
int play_game(int frm1, int frm2, int to1, int to2, int who, int matches, char usernames[100][500]);
#endif
