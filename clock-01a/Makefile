all: main run
	
run: main
	./main
main: *.cpp *.h
	g++ -std=c++98 *.cpp -o $@
clean:
	-rm -f *.o a.out core main
zip: clean
	zip ../clock-01a.zip *.md *.cpp *.h Makefile
.PHONY: all run clean zip
