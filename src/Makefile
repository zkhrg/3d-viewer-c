CC=gcc
FRONTEND=gui/cli/frontend.c
COMMON=brick_game/tetris/tetris/tetris.c  
BACKEND=brick_game/tetris/backend/backend.c
OTHER=brick_game/tetris/other/other.c
FLAGS=-Wall -Werror -Wextra -std=c11
APP_OBJECTS=$(APP_SOURCES:.c=.o)
RESULT=tetris.out
NCURSES=-lncurses
DIST_DIR=archive
TEST_FLAGS      := -lcheck -lm -lpthread #-lsubunit
GCOV_FLAGS      := -fprofile-arcs -ftest-coverage
VALGRIND_FLAGS := --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind.log
TEST_PARTS=$(wildcard brick_game/tetris/tests/test_parts/*.c)

OPEN_COMMAND =open
ifeq ($(OS), Linux)
	OPEN_COMMAND=xdg-open
else
	OPEN_COMMAND=open
endif

all: install run

install: $(FRONTEND) $(BACKEND) $(COMMON)
	$(CC) $(FLAGS) $^ -o $(RESULT) $(NCURSES)

uninstall: 
	@rm $(RESULT)
	@echo "Uninstalled"

run:
	./$(RESULT)  

dvi:
	$(OPEN_COMMAND) ../dvi/README.html

dist: clean_dist
	cd ../ && mkdir -p ${DIST_DIR}
	cd ../ && cp -rf src/brick_game ${DIST_DIR}/brick_game
	cd ../ && cp -rf src/gui ${DIST_DIR}/gui
	cd ../ && cp -rf src/Makefile ${DIST_DIR}/
	cd ../ && tar -czvf archive.tar.gz ${DIST_DIR}
	cd ../ && rm -rf ${DIST_DIR}

dist_unpack:
	cd ../ && tar -xzvf archive.tar.gz

test:
	@mkdir -p ./brick_game/tetris/tests/build
	$(CC) $(TEST_PARTS) ./brick_game/tetris/tests/test.c ${FLAGS} $(BACKEND) ${OTHER} -o ./test.out $(TEST_FLAGS)
	./test.out

style_check:
	@find .. -type f -name "*.c" -exec clang-format -n -style=Google {} \;
	@find .. -type f -name "*.h" -exec clang-format -n -style=Google {} \;
	@echo "Clang format style check is finished"

style:
	@find .. -type f -name "*.c" -exec clang-format -i -style=Google {} \;
	@find .. -type f -name "*.h" -exec clang-format -i -style=Google {} \;
	@echo "Clang format style apply is finished"

gcov_report:
	@mkdir -p report
	$(CC) $(TEST_PARTS) ./brick_game/tetris/tests/test.c $(BACKEND) ${OTHER} $(TEST_FLAGS) $(GCOV_FLAGS) -o ./gcov_report.out
	./gcov_report.out
	lcov -t "test" -o test.info -c -d .
	genhtml -o report/ test.info
	${OPEN_COMMAND} ./report/index.html
	make clean_gcov

test_valgrind:
	@mkdir -p ./brick_game/tetris/tests/build
	$(CC) $(TEST_PARTS) ./brick_game/tetris/tests/test.c ${FLAGS} $(BACKEND) ${OTHER} -o ./test.out $(TEST_FLAGS) 
	valgrind ${VALGRIND_FLAGS} ./test.out

clean: clean_project clean_static_lib clean_log clean_exec clean_obj clean_gcov clean_lcov clean_lcov_report clean_dist
	@echo "Clean finished"

clean_project:
	@find .. -type f -name "*.records" -exec rm {} \;

clean_dist:
	@cd ../ && rm -rf archive
	@cd ../ && rm -rf archive.tar.gz
clean_after_building:
	@rm -rf ${OBJ_DIR}
clean_static_lib:
	@find .. -type f -name "*.a" -exec rm {} \;
clean_log:
	@find .. -type f -name "*.log" -exec rm {} \;
clean_exec:
	@find .. -type f -name "*.out" -exec rm {} \;
clean_obj:
	@find .. -type f -name "*.o" -exec rm {} \;
clean_gcov:
	@find .. -type f -name "*.gcda" -exec rm {} \;
	@find .. -type f -name "*.gcno" -exec rm {} \;
clean_lcov:
	@find .. -type f -name "*.info" -exec rm {} \;
clean_lcov_report:
	@rm -rf report
