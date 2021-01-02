CXXFLAGS := -DJSMN_PARENT_LINKS -DJSMN_STRICT
LDFLAGS := -static

all: test_jsmn.exe simple.exe

cee.o:cee.cpp cee.hpp
	$(CXX) -c $<

test_jsmn.exe: jsmn.h test_jsmn.cpp cee.o
	$(CXX) -o $@ $(CXXFLAGS) test_jsmn.cpp cee.o $(LDFLAGS)

simple.exe: jsmn.h simple.c
	$(CC) -o $@ $(CXXFLAGS) simple.c $(LDFLAGS)

clean:
	rm -f *.o *.exe a.out