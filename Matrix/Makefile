TESTS_DIR = s21_test/
GCOV_DIR = s21_gcov/
BUILD_DIR = .

CFILES = s21_matrix.c 
TEST_CFILES = $(TESTS_DIR)s21_main_test.c $(TESTS_DIR)s21_matrix_operations_test.c
OFILES = $(CFILES:.c=.o)
TEST_OFILES = $(TEST_CFILES:.c=.o)
HEADER = %.h
LIB = s21_matrix.a

CC = gcc
CFLAGS = -Werror -Wextra -pedantic -std=c11
COVERAGE_FLAGS=-fprofile-arcs -ftest-coverage --coverage

ifeq ($(shell uname -s),Linux)
LDFLAGS=-lgcov -lcheck -lsubunit -lm -lrt -lpthread
endif
ifeq ($(shell uname -s),Darwin)
LDFLAGS=-lgcov -lcheck -lpthread
endif

all: clean start_gcov

$(TESTS_DIR)%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ 

s21_matrix: $(OFILES)
	$(CC) $(CFLAGS) -o $@ $^ 

$(LIB): $(OFILES)
	ar rc $@ $^

$(TESTS_DIR)$(LIB): CFLAGS += $(COVERAGE_FLAGS)
$(TESTS_DIR)$(LIB): $(TESTS_DIR)$(OFILES)
	ar rc $@ $^

$(TEST_OFILES): $(TESTS_DIR)%.o: $(TESTS_DIR)%.c  
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_OFILES) $(LIB) 
	$(CC) $(CFLAGS) -L. $^ -o $@ $(LDFLAGS)
	
$(TESTS_DIR)$(GCOV_DIR):
	mkdir -p $@

check: $(TEST_OFILES)  $(TESTS_DIR)$(LIB) 
	$(CC) $(CFLAGSs) -L. $^ -o $(TESTS_DIR)$(GCOV_DIR)$@ $(LDFLAGS)

gcov_report: $(TESTS_DIR)$(GCOV_DIR) check 
	$(TESTS_DIR)$(GCOV_DIR)check 
	geninfo $(TESTS_DIR) -o $(TESTS_DIR)coverage.info
	genhtml $(TESTS_DIR)coverage.info -o $(TESTS_DIR)coverage

start_gcov: gcov_report
	open $(TESTS_DIR)coverage/index.html

valgrind: test
	CK_FORK=no $@ --tool=memcheck --leak-check=yes --track-origins=yes -s  ./$^

clean:
	rm -f *.o *.a *.info *.gcda *.gcno test
	rm -f $(TESTS_DIR)*.o $(TESTS_DIR)*.a $(TESTS_DIR)*.info $(TESTS_DIR)*.gcda $(TESTS_DIR)*.gcno $(TESTS_DIR)*test
	rm -rf $(TESTS_DIR)$(GCOV_DIR)
	rm -rf $(TESTS_DIR)coverage
