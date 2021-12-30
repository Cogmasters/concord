CC ?= gcc

# https://github.com/cee-studio/cee-utils
CEE_UTILS_DIR ?= ../cee-utils

# folder to write the generated code to
WDIR := specs-code

JSON := $(sort $(wildcard */*.json))
APIS := $(sort $(patsubst %/, %, $(dir $(JSON))))

# Specs code-generator dependencies
SRC := $(CEE_UTILS_DIR)/cee-utils.c   \
       $(CEE_UTILS_DIR)/json-actor.c  \
       $(CEE_UTILS_DIR)/ntl.c         \
       $(CEE_UTILS_DIR)/json-string.c \
       $(CEE_UTILS_DIR)/log.c         \
       specs-gen.c

CFLAGS += -O0 -g -Wall -I$(CEE_UTILS_DIR)

# for inserting newlines at the end of each foreach
# see https://stackoverflow.com/questions/29651388/insert-a-new-line-in-a-makefile-foreach-loop
blank :=
define \n

$(blank)
endef

all: $(CEE_UTILS_DIR) | specs-gen.out
	@ rm -rf $(WDIR)/*/one-specs.h
	# Generate header files (specs-code/%/*.h)
	$(foreach VAR, $(JSON), ./specs-gen.out \
	  -h \
	  -o $(patsubst %, $(WDIR)/%, $(VAR:%.json=%.h)) \
	  $(VAR)$(\n))

	# Generate source files (specs-code/%/*.c)
	$(foreach VAR, $(JSON), ./specs-gen.out \
	  -c \
	  -o $(patsubst %, $(WDIR)/%, $(VAR:%.json=%.c)) \
	  -i $(filter $(APIS), $(subst /, ,$(dir $(VAR)))).h \
	  $(VAR)$(\n))

	# Generate single header (specs-code/%/one-specs.h)
	$(foreach VAR, $(JSON), ./specs-gen.out \
	  -O \
	  -a \
	  -o $(patsubst %, $(WDIR)/%, $(dir $(VAR))one-specs.h) \
	  $(VAR)$(\n))
	$(foreach VAR, $(JSON), ./specs-gen.out \
	  -E \
	  -a \
	  -o $(patsubst %, $(WDIR)/%, $(dir $(VAR))one-specs.h) \
	  $(VAR)$(\n))
	$(foreach VAR, $(JSON), ./specs-gen.out \
	  -S \
	  -a \
	  -o $(patsubst %, $(WDIR)/%, $(dir $(VAR))one-specs.h) \
	  $(VAR)$(\n))
	$(foreach VAR, $(JSON), ./specs-gen.out \
	  -F \
	  -a \
	  -o $(patsubst %, $(WDIR)/%, $(dir $(VAR))one-specs.h) \
	  $(VAR)$(\n))

specs-gen.out: $(SRC) | $(WDIR)
	$(CC) $(CFLAGS) -o $@ $(SRC) -lm

$(WDIR):
	mkdir -p $(addprefix $(WDIR)/, $(APIS))

echo:
	@ echo JSON: $(JSON)
	@ echo APIS: $(APIS)

clean:
	rm -rf $(WDIR) specs-gen.out

.PHONY : all echo clean
