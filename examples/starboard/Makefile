MAIN = src/main.o src/db.o src/bot.o src/commands.o src/starboard.o src/utils.o
COMMANDS = src/commands/ping.o src/commands/add.o src/commands/force.o src/commands/remove.o
OBJS = $(MAIN) $(COMMANDS)

PROGRAM = starboard

CC = cc
CCLD = cc
CFLAGS = -g -I/usr/local/include -std=c99
LDFLAGS = -ldiscord -lcurl -lpq -L/usr/local/lib

.SUFFIXES: .c .o

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(PROGRAM): $(OBJS)
	$(CCLD) -o $(PROGRAM) $(OBJS) $(LDFLAGS)

all: $(PROGRAM)

.PHONY: clean

clean:
	rm -f $(OBJS) $(PROGRAM) *.log