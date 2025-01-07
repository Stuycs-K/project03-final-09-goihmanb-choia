.PHONY: clean run compile

compile: compileClient compileServer

compileClient: pipe_networking.o base_client.o
	@gcc -o cl pipe_networking.o base_client.o

compileServer: pipe_networking.o base_server.o
	@gcc -o srv pipe_networking.o base_server.o

server: srv
	@./srv

client: cl
	@./cl

base_client.o: base_client.c pipe_networking.h base_client.h game.h
	@gcc -c basic_client.c

base_server.o: base_server.c pipe_networking.h base_server.h game.h
	@gcc -c base_server.c

pipe_networking.o: pipe_networking.c pipe_networking.h
	@gcc -c pipe_networking.c

clean:
	rm -rf *.o
	rm -rf cl srv
