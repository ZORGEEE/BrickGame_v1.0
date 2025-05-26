CPP= gcc -Wall -Werror -Wextra -std=c++20
CC= gcc -Wall -Werror -Wextra -std=c11

all: install run

install: uninstall clean frontend backend main.o
	$(CPP) main.o frontend_tetris.o backend_tetris.a frontend_snake.o backend_snake.a -lncurses -lstdc++ -o bin/game
	rm -rf *.o *.a 

run: install
	./bin/game

uninstall:
	rm -rf bin/game

clean: uninstall
	rm -rf *.o *.a *.gcda *.gcdo *.gcno  report *.tar *.out bin/desk

frontend:
	$(CPP) -c ./gui/cli/frontend_s.cpp -o frontend_snake.o
	$(CC) -c ./gui/cli/frontend.c -o frontend_tetris.o

backend:
	$(CPP) -c ./brick_game/snake/backend_s.cpp -o backend_snake.o
	ar rcs backend_snake.a backend_snake.o
	ranlib backend_snake.a
	$(CC) -c ./brick_game/tetris/backend.c -o backend_tetris.o
	ar rcs backend_tetris.a backend_tetris.o
	ranlib backend_tetris.a


main.o:
	$(CPP) -c main.cpp -o main.o