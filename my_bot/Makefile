# This Makefile assumes the top folder has been built

# Default build:
# 	$ make 
# Cleanup build:
# 	$ make clean
# Print this Makefile variables
# 	$ make echo

# If you are a Makefile newbie we recommend that you reading the following to
# 				better understand this file:
#
# Automatic Variables:
# 	gnu.org/software/make/manual/html_node/Automatic-Variables.html
# Prerequisite Types:
# 	gnu.org/software/make/manual/html_node/Prerequisite-Types.html

.SILENT: config

# relative location of concord/ to this Makefile
TOP = ..

# default compiler is gcc, but can be changed at the CLI
#    ex: '$ CC=clang make'
CC ?= gcc

LIBDIR := $(TOP)/lib
OBJDIR := obj

# add your source files here
SRC  := myBot.c
# this will match each individual .c file to a .o
OBJS := $(SRC:%.c=$(OBJDIR)/%.o)
# your bot executable's name
MAIN := myBot
# your bot config file
CONF := config.json

# -O0 no optimization
# -Wall emit 'all' warnings
# -g keep this for human-readable debugging
# -pthread tell the compiler to link the pthread library
#  			aswell configure compilation for threads
# -I add header folder to compiler search path
CFLAGS  := -O0 -g -Wall -pthread                       \
           -I. -I$(TOP)/include -I$(TOP)/cee-utils     \
           -I$(TOP)/common -I$(TOP)/common/third-party

# -L add library folder to compiler search path
# -ldiscord links against libdiscord.a
# -lcurl links against libcurl, a concord dependency
LDFLAGS := -L$(LIBDIR) -ldiscord -lcurl

all: $(MAIN) $(CONF)

# Compile the bot executable with the given the object files
$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Make sure the obj directory exists before building the object files
$(OBJS): | $(OBJDIR)

$(OBJDIR):
	@ mkdir -p $(OBJDIR)

# Match each .o file to its .c counterpart (foo.o: foo.c)
$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(CONF):
	cp -n $(TOP)/config.json $(CONF)
	echo "A template config file was copied into this folder."
	echo "Replace 'YOUR-BOT-TOKEN' with an actual token at $(CONF)"

clean:
	rm -rf $(MAIN)
	rm -rf $(OBJDIR)

echo:
	@ echo -e 'CC: $(CC)\n'
	@ echo -e 'SRC: $(SRC)\n'
	@ echo -e 'OBJS: $(OBJS)\n'
	@ echo -e 'MAIN: $(MAIN)\n'

.PHONY: all clean config
