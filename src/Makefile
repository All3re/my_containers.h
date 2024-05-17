CC=g++
CFLAGS=-Wall -Werror -Wextra -g -lstdc++ -std=c++17
GTEST=-lgtest -lgtest_main -pthread
COVER=-coverage

# # # # # ----------------------------------------------------------
all: test

test: clean
	g++ $(CFLAGS) $(COVER) ./tests/vector_test.cpp ./tests/list_test.cpp ./tests/queue_test.cpp ./tests/array_test.cpp -o test $(GTEST)
	./test

gcov_report: test
	gcov list_test.gcda queue_test.gcda vector_test.gcda
	gcovr
	gcovr --html-details -o report.html


clean:
	rm -rf test
	rm -rf *.a *.o *.out
	rm -rf *.info *.gcda *.gcno *.gcov *.gch *.dSYM *.html
	rm -rf coverage
	rm -rf gcov_report report
