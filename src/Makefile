UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
    CC = gcc
	CFLAGS := -std=c11 -lcheck -lsubunit -pthread -lrt -lm -Wall -Werror -Wpedantic
else
    CC = gcc
	CFLAGS :=  -Wall -Werror -Wextra -std=c11 
endif

TESTFLAGS = -lcheck
GCOVFLAGS = -fprofile-arcs -ftest-coverage

OBJS := out/main.o out/frontend.o out/backend.o


.PHONY: all install uninstall clean dvi dist

all: install dist

tetris: $(OBJS)
	$(CC) $^ -o build/$@ $(CFLAGS) -lncurses

out/%.o: ./%.c
	$(CC) $(CFLAGS) -c $< -o $@

out/%.o: gui/cli/%.c
	$(CC) $(CFLAGS) -c $< -o $@

out/%.o: brick_game/tetris/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean: uninstall
	$(RM) out/*.o Tetris_Game.v1.tar.gz
	@rm -rf *.gcno *gcda *.gcov gcov
	@rm -rf report report.info
	@rm -rf *.dSYM
	@rm -rf *.o *.a test
	@rm -f score.txt
	@rm -f tests/test.o brick_game/tetris/*.o


folder_out:
	mkdir -p out
	mkdir -p build

install: folder_out tetris

uninstall:
	rm -rf build

dvi:
	open dvi.md

dist:
	tar -cvf Tetris_Game.v1.tar.gz brick_game gui main.c defines.h makefile

run: 
	cd build && ./tetris

style_check:
	clang-format --style=google -n $$(find . -type f -name "*.c" -print0 | xargs -0)
	clang-format --style=google -n $$(find . -type f -name "*.h" -print0 | xargs -0)

style_correction:
	clang-format --style=google -i $$(find . -type f -name "*.c" -print0 | xargs -0)
	clang-format --style=google -i $$(find . -type f -name "*.h" -print0 | xargs -0)

test:
	$(CC) tests/test.c brick_game/tetris/backend.c -o $@ $(CFLAGS) -lncurses $(TESTFLAGS) $(GCOVFLAGS)
	./test

gcov_report: test
	@lcov -t "./gcov" -o report.info --no-external -c -d .
	@genhtml -o report report.info
	@open ./report/index.html
