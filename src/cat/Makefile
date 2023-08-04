CC = gcc
FLAGS = -Wall -Wextra -Werror
CLANGFILE = s21_cat.c s21_cat.h

all : clean s21_cat

s21_cat:
		$(CC) $(FLAGS) -o s21_cat s21_cat.c

rebuild: clean all

clean:
	rm -rf s21_cat

clang-check:
		cp ../materials/.clang-format .
		clang-format -n -style=Google $(CLANGFILE)
		rm -f .clang-format

clang-format:
		cp ../materials/.clang-format .
		clang-format -i -style=Google $(CLANGFILE)
		rm -f .clang-format
