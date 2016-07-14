sim: copied_files main.o board.o sjlogo.o image.o
	g++ $(shell fltk-config --ldflags) -o sim main.o board.o sjlogo.o image.o

%.o: %.cpp platform.h
	g++ $(shell fltk-config --cxxflags) -c -o $@ $<

copied_files:
	cp ../sjlogo/*.cpp ../sjlogo/*.h ../sjlogo/*.c .

clean:
	rm -f *.o sim sjlogo.cpp image.*
