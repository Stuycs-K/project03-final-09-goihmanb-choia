.PHONY: clean run compile

compile: compileClient compileServer compileLeaderboard

compileClient: pipe_networking.o base_client.o
	@gcc -o cl pipe_networking.o base_client.o

compileServer: pipe_networking.o base_server.o
	@gcc -o srv pipe_networking.o base_server.o

compileLeaderboard: leaderboard.o
	@gcc -o leaderboard leaderboard.o

server: srv
	@./srv

client: cl
	@./cl

leaderboard: leaderboard
	@./leaderboard

base_client.o: base_client.c pipe_networking.h base_client.h game.h
	@gcc -c base_client.c

base_server.o: base_server.c pipe_networking.h base_server.h game.h
	@gcc -c base_server.c

pipe_networking.o: pipe_networking.c pipe_networking.h
	@gcc -c pipe_networking.c

leaderboard.o: game.h base_client.h base_server.h
	@gcc -c leaderboard.c

clean:
	rm -rf *.o
	rm -rf cl srv leaderboard
