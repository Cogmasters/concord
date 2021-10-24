# This Makefile assumes the top folder has been built
.SILENT: config

TOP = ..

# CC default compiler is gcc, can be changed
#    ex: 'CC=clang make'
CC     ?= gcc
LIBDIR := $(TOP)/lib

# SRC contains all .c files from this folder
SRC  := $(wildcard ./*.c)
# EXES replaces all .c extensions from SRC with .out
EXES := $(patsubst %.c, %.out, $(SRC))

# -O0 no optimization
# -Wall emit warnings
# -g keep this for debugging with gdb
# -pthread tell the compiler to link the pthread library
#  			aswell configure compilation for threads
# -I links to a folder where a header dependency resides
CFLAGS  := -O0 -g -Wall -pthread                       \
           -I. -I$(TOP) -I$(TOP)/cee-utils             \
           -I$(TOP)/common -I$(TOP)/common/third-party \

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

config:
	cp -n $(TOP)/config.json ./mybot_config.json
	echo "A template config file was copied into this folder."
	echo "Replace 'YOUR-BOT-TOKEN' with an actual token in mybot_config.json ."

.PHONY: all clean
