TOP = ..

CC     ?= gcc
LIBDIR := $(TOP)/lib

SRC  := $(wildcard ./*.c)
EXES := $(patsubst %.c, %.out, $(SRC))

CFLAGS  := -I. -I$(TOP) -Wall -std=c11 -O0 -g
LDFLAGS := -L$(LIBDIR) -ldiscord -lcurl -lcrypto -lpthread -lm

%.out: %.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

all: $(EXES)

clean:
	rm -rf $(EXES)

.PHONY: all clean
