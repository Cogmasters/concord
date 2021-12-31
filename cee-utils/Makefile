CC ?= gcc

OBJDIR   := obj
TEST_DIR := test

SRC := $(wildcard *.c)
OBJS := $(SRC:%.c=$(OBJDIR)/%.o)

CFLAGS += -std=c89 -O0 -g            \
          -Wall -Wno-unused-function \
          -I. -DLOG_USE_COLOR

ifneq ($(release),1)
	CFLAGS += -D_STATIC_DEBUG
endif

ifeq ($(DEBUG_JSON),1)
	CFLAGS += -D_STRICT_STATIC_DEBUG
endif

ifeq ($(CC),stensal-c)
	CFLAGS += -D_DEFAULT_SOURCE
else
	CFLAGS += -fPIC -D_XOPEN_SOURCE=700
endif

LDFLAGS += -lm

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(OBJS)

test: all
	$(MAKE) -C $(TEST_DIR)

$(OBJS): | $(OBJDIR)

$(OBJDIR) :
	mkdir -p $(OBJDIR)

echo:
	@ echo -e 'SRC: $(SRC)'
	@ echo -e 'OBJS: $(OBJS)'

clean: 
	rm -rf $(OBJDIR)
	$(MAKE) -C $(TEST_DIR) clean

.PHONY : all test echo clean
