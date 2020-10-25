all: main run

run: main
	./main
main:
	g++ -std=c++14 *.cpp -o $@
clean:
	-rm -f *.o a.out core main
zip:
	zip ../clock-04.zip *.txt *.cpp *.h Makefile
.PHONY: all run clean zip

