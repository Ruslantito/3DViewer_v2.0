FLAGS=-Wall -Wextra -Werror -std=c++17 -pedantic
GTEST=-lgtest -lgtest_main -pthread
COVER=-fprofile-arcs -ftest-coverage
ASAN=#-fsanitize=address -fanalyzer

.PHONY: all
all: install start

.PHONY: install
install:
	cmake -S . -B ./build && cd ./build && make

start:
	./build/3DViewer

.PHONY: uninstall
uninstall:
	rm -rf build

.PHONY: open
open:
	cd build && ./3DViewer

.PHONY: clean
clean:
	rm -rf build
	rm -rf 3DViewer_2.0
	rm -f 3DViewer_2.0.tar.gz
	rm -f *.info *.gcda *.gcno *.gcov *.css *.html
	rm -rf coverage
	rm -rf test

.PHONY: dvi
dvi: 
	makeinfo --html 3DViewer_2.0.texi
	open 3DViewer_2.0/index.html 

.PHONY: dist
dist:
	tar czvf 3DViewer_2.0.tar.gz ./Model ./View ./Controller ./QtGifImage-master \
	CMakeLists.txt main.cc Makefile 3DViewer_2.0.texi

.PHONY: tests
tests: 
	rm -f *.gcda *.gcno
	g++ $(FLAGS) $(ASAN) $(GTEST) $(COVER) \
	./Testing/tests.cc ./Model/Model.cc ./Model/ActionFacede.cc -o test
	./test
	geninfo . -b . -o ./coverage.info --no-external
	genhtml coverage.info -o ./coverage

.PHONY: gcov_report
gcov_report:
	open coverage/index.html

lint:
	clang-format -n *.cc ./Model/*.cc ./View/*.cc
	clang-format -n ./Model/*.h ./View/*.h ./Controller/*.h

leaks:
	leaks -atExit -- ./test

