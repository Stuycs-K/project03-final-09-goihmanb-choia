#ifndef GAME_H
#define GAME_H

#define MOVE_REGULAR 0
#define MOVE_WIN 1
#define MOVE_LOSE -1
#define MOVE_TIE 2
#define TOURNAMENT_WIN 3
#define TOURNAMENT_LOSE 4
#define O 4
#define X 5
#define BYE 6
#define YOUR_TURN 3
#define OPPONENT_TURN 4

#define P1WIN 0
#define P2WIN 1

#define LEADERBOARD_FILE "leaderboard.dat"
#define GS sizeof(struct game_move)


struct game_move {
	int row;
	int col;
	int msg_type;
	int ismove;
	// 0 for false, 1 for true
	int won;
};

struct leaderboard_stats {
	char username[500];
	int wins;
	int losses;
};

struct game_pipes {
	int from1, to1;
	int from2, to2;
	int pid1, pid2;
};

#endif
