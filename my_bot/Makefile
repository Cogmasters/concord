# This Makefile assumes the top folder has been built

TOP = ..

# CC default compiler is gcc, can be changed
#    ex: 'CC=clang make'
CC     ?= gcc
LIBDIR := $(TOP)/lib

# SRC contains all .c files from this folder
SRC  := $(wildcard ./*.c)
# EXES replaces all .c extensions from SRC with .out
EXES := $(patsubst %.c, %.out, $(SRC))

# -I links to a folder where a header dependency resides
# -Wall emit warnings
# -std=c11 tells the compiler to build against c11 standard
# -O0 no optimization
# -g keep this for debugging with gdb
CFLAGS  := -I. -I$(TOP) -I$(TOP)/cee-utils             \
           -I$(TOP)/common -I$(TOP)/common/third-party \
           -Wall -std=c11 -O0 -g

# -L links to a folder where a lib dependency resides
# -ldiscord links against libdiscord.a
# -lcurl links against libcurl, a orca dependency
# -lcrypto links against OpenSSL, a libcurl dependency
# -lpthread links against POSIX threads, a orca dependency
# -lm links against math.h, a orca dependency
LDFLAGS := -L$(LIBDIR) -ldiscord -lcurl -lcrypto -lpthread -lm

# This will match each .out to a .c and compile the executable
#     ex: 'foo.out: foo.c'
# For $@ and $^ explanation, see:
#     gnu.org/software/make/manual/html_node/Automatic-Variables.html
%.out: %.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

all: $(EXES)

clean:
	rm -rf $(EXES)

.PHONY: all clean
