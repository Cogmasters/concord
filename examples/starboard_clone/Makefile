OBJS = src/memhandl.o src/utils.o src/db.o src/main.o
PROGRAM = sbclone

CC = gcc
CCLD = gcc
CFLAGS = -g -I/usr/local/include
LDFLAGS = -ldiscord -lcurl -lsqlite3 -lpthread -L/usr/local/include

.SUFFIXES: .c .o

.c.o:
	$(CC) -c $< -o $@

$(PROGRAM): $(OBJS)
	$(CCLD) -o $(PROGRAM) $(OBJS) $(LDFLAGS)

all: $(PROGRAM)

.PHONY: clean

clean:
	rm -f $(OBJS) $(PROGRAM) *.db *.log
