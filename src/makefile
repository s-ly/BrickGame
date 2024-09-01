CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 
BACKEND_FILES = $(wildcard ./brick_game/tetris/*.c)
GUI_FILES = $(wildcard ./gui/cli/*.c)
ALL_C_FILES = $(wildcard ./gui/cli/*.c ./brick_game/tetris/*.c ./tests/*.c)
ALL_H_FILES = $(wildcard ./gui/cli/*.h ./tests/*.h)
LIB = -lncurses
LIB_TEST = -lcheck

ifeq ($(shell uname),Linux)
	LIB_TEST += -lm -lsubunit
endif


all: clean install

install: libtetris_back.a $(GUI_FILES)
	$(CC) $(CFLAGS) $(GUI_FILES) libtetris_back.a $(LIB) -o tetris_game
	./tetris_game
	rm -rf *.o

uninstall:
	rm -rf tetris_game
	rm -rf record

test: clean 
	$(CC) $(BACKEND_FILES) --coverage tests/test.c -o test $(LIB) $(LIB_TEST)
	./test

gcov_report: test
	lcov -t "result" -o res.info -c -d .
	genhtml -o report res.info
	open report/index.html
	rm -rf *gcda *gcno res.info test

tetris_back.o: 
	$(CC) -c $(BACKEND_FILES)

libtetris_back.a: tetris_back.o
	ar rc libtetris_back.a *.o
	ranlib libtetris_back.a

dist:
	tar -czvf archive.tar.gz ./*

dvi: doc/manual.tex
	latex $<

clean:
	rm -rf *.out
	rm -rf *.o
	rm -rf *.a
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf tetris_game
	rm -rf test
	rm -rf report
	rm -rf *.aux *.log
	rm -rf record

clang:
	clang-format -n -style=google $(ALL_C_FILES)  
	clang-format -n -style=google $(ALL_H_FILES)  
clang_repair:
	clang-format -i -style=google $(ALL_C_FILES)  
	clang-format -i -style=google $(ALL_H_FILES)