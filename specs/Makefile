CC ?= gcc

API ?= discord

API_H       ?= $(API).h
API_SPECS_H ?= $(API)-specs.h

# https://github.com/Cogmasters/cog-utils
COGUTILS_DIR ?= ../cog-utils

RDIR := api
WDIR := code

MAIN := main

JSON := $(sort $(wildcard $(RDIR)/*.json))

# code-generator dependencies
DEPS := $(COGUTILS_DIR)/cog-utils.c   \
        $(COGUTILS_DIR)/json-actor.c  \
        $(COGUTILS_DIR)/ntl.c         \
        $(COGUTILS_DIR)/json-string.c \
        $(COGUTILS_DIR)/log.c

# default CFLAGS
CFLAGS  += -O0 -g -Wall -Wno-unused-function -I$(COGUTILS_DIR)

blank :=
define \n

$(blank)
endef

define generate_source
	# Generate source files
	$(foreach VAR, $(JSON), ./$(MAIN) \
	  -c \
	  -o $(VAR:$(RDIR)/%.json=$(WDIR)/%.c) \
	  -i $(API_H) \
	  $(VAR)$(\n))
endef

define generate_headers
	# Generate header files
	$(foreach VAR, $(JSON), ./$(MAIN) \
	  -h \
	  -o $(VAR:$(RDIR)/%.json=$(WDIR)/%.h) \
	  $(VAR)$(\n))
endef

define generate_headers_amalgamation
	@ rm -rf $(WDIR)/$(API)-specs.h
	# Generate single header
	$(foreach VAR, $(JSON), ./$(MAIN) \
	  -O \
	  -a \
	  -o $(WDIR)/$(API_SPECS_H) \
	  $(VAR)$(\n))
	$(foreach VAR, $(JSON), ./$(MAIN) \
	  -E \
	  -a \
	  -o $(WDIR)/$(API_SPECS_H) \
	  $(VAR)$(\n))
	$(foreach VAR, $(JSON), ./$(MAIN) \
	  -S \
	  -a \
	  -o $(WDIR)/$(API_SPECS_H) \
	  $(VAR)$(\n))
	$(foreach VAR, $(JSON), ./$(MAIN) \
	  -F \
	  -a \
	  -o $(WDIR)/$(API_SPECS_H) \
	  $(VAR)$(\n))
endef

all: $(COGUTILS_DIR) 
	$(MAKE) gen_source gen_headers gen_headers_amalgamation

gen_source: | $(WDIR)
	$(generate_source)

gen_headers: | $(WDIR)
	$(generate_headers)

gen_headers_amalgamation: | $(WDIR)
	$(generate_headers_amalgamation)

$(WDIR): | $(MAIN)
	mkdir -p $@

$(MAIN): $(MAIN).c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $^ -lm

echo:
	@ echo -e 'JSON: $(JSON)\n'
	@ echo -e 'API: $(API)\n'
	@ echo -e 'API_H: $(API_H)\n'
	@ echo -e 'API_SPECS_H: $(API_SPECS_H)\n'
	@ echo -e 'MAIN: $(MAIN)\n'
	@ echo -e 'CFLAGS: $(CFLAGS)\n'

clean:
	rm -rf $(WDIR) $(MAIN)

.PHONY : all echo clean
