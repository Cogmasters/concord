CC ?= gcc

MAIN := specs-gen

# https://github.com/cee-studio/cee-utils
CEEUTILS_DIR ?= ../cee-utils

OBJDIR := obj
WDIR   := specs-code

JSON := $(sort $(wildcard */*.json))
APIS := $(sort $(patsubst %/, %, $(dir $(JSON))))

# specs code-generator dependencies
DEPS := $(CEEUTILS_DIR)/cee-utils.c   \
        $(CEEUTILS_DIR)/json-actor.c  \
        $(CEEUTILS_DIR)/ntl.c         \
        $(CEEUTILS_DIR)/json-string.c \
        $(CEEUTILS_DIR)/log.c
OBJS := $(JSON:%.json=$(OBJDIR)/%.o)

# needed for 'make build'
# https://github.com/cee-studio/orca/common (common.h and common.c)
COMMON_DIR ?= ../common
CFLAGS  ?= -I. -I..
LDFLAGS ?= -L../lib

# default CFLAGS
CFLAGS  += -O0 -g -Wall -Wno-unused-function -I$(CEEUTILS_DIR)

# for inserting newlines at the end of each foreach
# see https://stackoverflow.com/questions/29651388/insert-a-new-line-in-a-makefile-foreach-loop
blank :=
define \n

$(blank)
endef

define generate_source
	# Generate source files (specs-code/%/*.c)
	$(foreach VAR, $(JSON), ./$(MAIN) \
	  -c \
	  -o $(patsubst %, $(WDIR)/%, $(VAR:%.json=%.c)) \
	  -i $(filter $(APIS), $(subst /, ,$(dir $(VAR)))).h \
	  $(VAR)$(\n))
endef

define generate_header
	@ rm -rf $(WDIR)/*/one-specs.h
	# Generate single header (specs-code/%/one-specs.h)
	$(foreach VAR, $(JSON), ./$(MAIN) \
	  -O \
	  -a \
	  -o $(patsubst %, $(WDIR)/%, $(dir $(VAR))one-specs.h) \
	  $(VAR)$(\n))
	$(foreach VAR, $(JSON), ./$(MAIN) \
	  -E \
	  -a \
	  -o $(patsubst %, $(WDIR)/%, $(dir $(VAR))one-specs.h) \
	  $(VAR)$(\n))
	$(foreach VAR, $(JSON), ./$(MAIN) \
	  -S \
	  -a \
	  -o $(patsubst %, $(WDIR)/%, $(dir $(VAR))one-specs.h) \
	  $(VAR)$(\n))
	$(foreach VAR, $(JSON), ./$(MAIN) \
	  -F \
	  -a \
	  -o $(patsubst %, $(WDIR)/%, $(dir $(VAR))one-specs.h) \
	  $(VAR)$(\n))
endef

$(OBJDIR)/%.o : $(WDIR)/%.c
	$(CC) -I$(COMMON_DIR) $(CFLAGS) -c -o $@ $< $(LDFLAGS)

all: $(CEEUTILS_DIR) $(WDIR)

build: all
	$(MAKE) $(OBJS)

$(WDIR): | $(MAIN)
	mkdir -p $(addprefix $(WDIR)/, $(APIS))
	$(generate_source)
	$(generate_header)

$(MAIN): $(MAIN).c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $^ -lm

$(OBJS): | $(OBJDIR)

$(OBJDIR):
	mkdir -p $(addprefix $(OBJDIR)/, $(APIS))

echo:
	@ echo -e 'JSON: $(JSON)\n'
	@ echo -e 'APIS: $(APIS)\n'
	@ echo -e 'MAIN: $(MAIN)\n'
	@ echo -e 'OBJS: $(OBJS)\n'
	@ echo -e 'CFLAGS: $(CFLAGS)\n'
	@ echo -e 'LDFLAGS: $(LDFLAGS)\n'

clean:
	rm -rf $(WDIR) $(OBJDIR) $(MAIN)

.PHONY : all build echo clean
