all: s21_grep

s21_grep: s21_grep.o
		gcc -Wall -Werror -Wextra s21_grep.o -o s21_grep

s21_grep.o: 
		gcc -c -Wall -Werror -Wextra s21_grep.c -o s21_grep.o

clean:
	rm -f s21_grep.o s21_grep