X1 = -DLC_SIMPLE_IMPLEMENTATION -DOC_SIMPLE_IMPLEMENTATION
X2 = -DLC_SIMPLE_IMPLEMENTATION
X3 =                            -DOC_SIMPLE_IMPLEMENTATION
X4 =

all: main run

run: main
	./main
main: *.cpp *.h
	g++ -std=c++14 $(X4) *.cpp -o $@
clean:
	-rm -f *.o a.out core main
zip: clean
	zip ../clock-04x.zip *.txt *.cpp *.h
.PHONY: all run clean zip

