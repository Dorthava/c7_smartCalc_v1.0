CC = gcc
CFLAGS = -Wall -Wextra -Werror
OBJ := s21_stack.c s21_smartcalc.c s21_additional.c
GCOVFLAGS:=-fprofile-arcs -ftest-coverage
LDFLAGS:=-lcheck -lgcov -fprofile-arcs --coverage
APP = build/s21_calc.app
ifeq ($(shell uname), Linux)
LDFLAGS +=-pthread -lcheck_pic -lrt -lm -lsubunit
endif

OBJECTS = $(addprefix obj/,$(OBJ:.c=.o))

OBJECTS_GCOV = $(addprefix gcov_obj/,$(OBJ:.c=.o))

all: install s21_smartcalc.a test

s21_smartcalc.a: $(OBJECTS)
	ar -src s21_smartcalc.a $(OBJECTS)

s21_smartcalc_gcov.a: $(OBJECTS_GCOV)
	ar -src s21_smartcalc_gcov.a $(OBJECTS_GCOV)

test: s21_smartcalc_gcov.a
	$(CC) $(CFLAGS) -c Test/*.c -o gcov_obj/tests.o
	$(CC) gcov_obj/tests.o s21_smartcalc_gcov.a -o $@ $(LDFLAGS) $(GCOVFLAGS)
	./test

gcov_report: test
	lcov -t "test" -o test.info -c -d .  
	genhtml test.info --output-directory report
	open ./report/index.html

gcov_obj/%.o: %.c
	$(CC) $(CFLAGS) $(GCOVFLAGS) -c $< -o $@

obj/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

build:
	mkdir build
	cd build && qmake ../SmartCalc/ && make && mv SmartCalc s21_calc.app

install: uninstall build
	@mkdir $(HOME)/Desktop/SmartCalc_v1.0/
	@cp -rf $(APP) $(HOME)/Desktop/SmartCalc_v1.0/

uninstall:
	rm -rf build
	rm -rf $(HOME)/Desktop/SmartCalc_v1.0/

dist:
	rm -rf Archive_SmartCalc_v1.0/
	mkdir Archive_SmartCalc_v1.0
	mkdir Archive_SmartCalc_v1.0/src
	cp 	Makefile *.c Test/*.c *.h SmartCalc/SmartCalc.pro SmartCalc/*.cpp SmartCalc/*.h SmartCalc/*.ui Archive_SmartCalc_v1.0/src/
	tar cvzf Archive_SmartCalc_v1.0.tgz Archive_SmartCalc_v1.0/
	mv Archive_SmartCalc_v1.0.tgz $(HOME)/Desktop/
	rm -rf Archive_SmartCalc_v1.0/
	
dvi:
	open dvi.html

clean:
	rm -rf test *.gcov *.css gcov*.html test.info
	rm -rf *.o *.a *.out SmartCalc/.qmake.stash SmartCalc/*.user
	rm -rf gcov_obj/*.gcda gcov_obj/*.gcno gcov_obj/*.o 
	rm -rf obj/*.o  
	rm -rf report
	rm -rf ./build*

style: 
	clang-format --style=google *.c *.h SmartCalc/*.cpp SmartCalc/*.h Test/tests.c -n

correct_style: 
	clang-format --style=google *.c *.h SmartCalc/*.cpp SmartCalc/*.h Test/tests.c -i

valgrind:
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./test