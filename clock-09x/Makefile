all: main run

run: main
	./main
main: *.cpp *.h
	g++ -std=c++14 *.cpp -o $@
unit_tests: *.cpp *.h
	g++ -std=c++14 -DUNIT_TESTING *.cpp -o unit_tests
	@./unit_tests
clean:
		-rm -f *.o a.out core main unit_tests
zip: clean
	zip ../clock-09x.zip *.txt *.cpp *.h Makefile
.PHONY: all run unit_tests clean zip

