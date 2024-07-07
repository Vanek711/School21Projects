SRCMODULES = arithmetic.c compare.c convert.c rounding.c s21_decimal_type.c
OBJMODULES = $(SRCMODULES:.c=.o)
HEADERS = %.h s21_decimal.h s21_decimal_type.h

CC = gcc
CFLAGS = -Wall -std=c11 -pedantic -Werror
LIB = s21_decimal.a

CHKDIR = check/
CHKBLDDIR = $(CHKDIR)build/
CHKOBJMODULES = $(OBJMODULES:%=$(CHKBLDDIR)%)
CHKBIN = check
CHKCFLAGS = $(shell pkg-config --cflags check)
CHKLIBS = $(shell pkg-config --libs check)

GCOVBLDDIR = $(CHKBLDDIR)gcov/
GCOVOBJMODULES = $(OBJMODULES:%=$(GCOVBLDDIR)%)
GCOVCFLAGS = -fprofile-arcs -ftest-coverage
GCOVLIBS = -lgcov

all: $(LIB) test

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(LIB): CPPFLAGS = -DNDEBUG
$(LIB): $(OBJMODULES)
	ar rcs $@ $^

$(GCOVBLDDIR):
	mkdir -p $@

$(GCOVBLDDIR)%.o: %.c $(HEADERS) $(GCOVBLDDIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(GCOVBLDDIR)$(LIB): CFLAGS += $(GCOVCFLAGS)
$(GCOVBLDDIR)$(LIB): $(GCOVOBJMODULES)
	ar rcs $@ $^

$(CHKBLDDIR):
	mkdir -p $@

$(CHKBLDDIR)%.o: $(CHKDIR)%.c $(CHKDIR)%.h $(HEADERS) $(CHKBLDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(CHKBLDDIR)$(CHKBIN): $(CHKDIR)main.c $(CHKOBJMODULES) $(GCOVBLDDIR)$(LIB)
	$(CC) $(CFLAGS) $^ -o $@ $(GCOVLIBS) $(CHKLIBS)

test: $(CHKBLDDIR)$(CHKBIN)
	$<

gcov_report: test
	geninfo $(GCOVBLDDIR) -o $(GCOVBLDDIR)coverage.info
	genhtml $(GCOVBLDDIR)coverage.info -o $(GCOVBLDDIR)coverage

cppcheck:
	$@ --enable=all --suppress=missingIncludeSystem .

valgrind: $(CHKBLDDIR)$(CHKBIN)
	CK_FORK=no $@ --tool=memcheck --leak-check=yes $<

leaks: $(CHKBLDDIR)$(CHKBIN)
	CK_FORK=no $@ -atExit -- $<

gdb lldb: $(CHKBLDDIR)$(CHKBIN)
	CK_FORK=no $@ $<

format:
	clang-format -i {,$(CHKDIR)}*.{c,h}

clean:
	rm -f *.o $(LIB)
	rm -rf $(CHKBLDDIR){*.o,$(CHKBIN),$(CHKBIN).dSYM}
	rm -f $(GCOVBLDDIR){*.o,$(LIB),*.gcno,*.gcda}
	rm -rf $(GCOVBLDDIR){coverage.info,coverage}
