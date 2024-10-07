GCC=gcc -Wall -Werror -Wextra -g # -fsanitize=address
SRC=s21_matrix_oop.cpp
OBJ=s21_matrix_oop.o
CFLAGS=--std=c++17 -lstdc++ -lm
TESTFLAGS=-lgtest -lgcov

all: clean test

clean:
	rm -rf *.o *.a test

test: s21_matrix_oop.a
	$(GCC) -g s21_matrix_oop_test.cpp s21_matrix_oop.a $(CFLAGS) $(TESTFLAGS) -o test
	./test

s21_matrix_oop.a: clean
	$(GCC) -c $(SRC) $(CFLAGS)
	ar rcs s21_matrix_oop.a $(OBJ)

# check: test
# 	clang-format -style="{BasedOnStyle: Google}" -i *.cpp *.h
# 	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config *.cpp *.h
# ifeq ($(OS), Darwin)
# 	leaks --atExit -- test
# else
# 	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes ./test
# endif
