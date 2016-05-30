sim: copied_files main.o board.o sjlogo.o
	g++ $(shell fltk-config --ldflags) -o sim main.o board.o sjlogo.o

%.o: %.cpp platform.h
	g++ $(shell fltk-config --cxxflags) -c -o $@ $<

copied_files: ../sjlogo/sjlogo.cpp ../sjlogo/platform.h
	cp ../sjlogo/sjlogo.cpp ../sjlogo/platform.h .

clean:
	rm -f *.o sim sjlogo.cpp platform.h
