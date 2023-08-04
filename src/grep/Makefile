CC = gcc
FLAGS = -Wall -Wextra -Werror
CLANGFILE = s21_grep.c s21_grep.h

all : clean s21_grep

s21_grep:
		$(CC) $(FLAGS) -o s21_grep s21_grep.c

rebuild: clean all

clean:
		rm -rf s21_grep

clang-check:
		cp ../materials/.clang-format .
		clang-format -n -style=Google $(CLANGFILE)
		rm -f .clang-format


clang-format:
		cp ../materials/.clang-format .
		clang-format -i -style=Google $(CLANGFILE)
		rm -f .clang-format
