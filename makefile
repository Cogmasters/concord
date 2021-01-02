all: test_jsmn.exe

cee.o:cee.cpp cee.hpp
	$(CXX) -c $<

test_jsmn.exe: jsmn.h test_jsmn.cpp cee.o
	$(CXX) -o $@ test_jsmn.cpp cee.o

clean:
	rm -f *.o *.exe a.out
