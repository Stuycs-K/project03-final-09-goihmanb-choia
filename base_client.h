#ifndef BASE_CLEINT_H
#define BASE_CLEINT_H
void game_loop(int to_server, int from_server, int my_pid);
void write_to_server(struct game_move move, int board[3][3], int to_server, int my_character);
char * format_brd(int board[3][3], char ret[1000]);
int checkforcond(int plyr, int board[3][3], struct game_move move);
#endif
