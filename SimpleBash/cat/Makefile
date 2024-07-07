
all: s21_cat

s21_cat: s21_cat.o
		gcc -Wall -Werror -Wextra s21_cat.o -o s21_cat

s21_cat.o: 
		gcc -c -Wall -Werror -Wextra s21_cat.c -o s21_cat.o

clean:
	rm -f s21_cat.o s21_cat 
