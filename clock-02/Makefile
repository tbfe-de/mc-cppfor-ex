all: main run
	
run: main
	./main
main: *.cpp *.h
	g++ -std=c++14 *.cpp -o $@
clean:
	-rm -f *.o a.out core main
zip: clean
	zip ../clock-02.zip *.md *.cpp *.h Makefile
.PHONY: all run clean zip
