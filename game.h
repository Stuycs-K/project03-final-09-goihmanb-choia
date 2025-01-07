#ifndef GAME_H
#define GAME_H

#define MOVE_REGULAR 0
#define MOVE_WIN 1
#define MOVE_LOSE -1
#define MOVE_TIE 2
#define O 0
#define X 1

struct game_move {
	int row;
	int col;
	int msg_type;
	int pid;
};

struct game_pipes {
	int from1, to1;
	int from2, to2;
	int pid1, pid2;
};

#endif
