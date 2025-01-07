#ifndef BASE_SERVER.H
#define BASE_SERVER.H
void write_stats(int wol,char user[500]);
int check_board(int board [][]);
char * get_display(int board [][]);
char * display_leaderboard (FILE * f);
#endif
