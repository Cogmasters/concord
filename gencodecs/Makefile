TOP = ../..
CC ?= gcc
PP := ./gencodecs-pp

INCLUDE_DIR := $(TOP)/include
API_DIR     := api
OBJ_DIR     := $(TOP)/obj

TEMPLATES_IN    := discord-codecs.H
TEMPLATES_OUT_C := $(TEMPLATES_IN:%.H=%.c)
TEMPLATES_OUT_H := $(TEMPLATES_IN:%.H=%.h)

OBJS := $(OBJ_DIR)/jsmn-find.o $(OBJ_DIR)/json-build.o \
        $(TEMPLATES_OUT_C:%.c=$(OBJ_DIR)/%.o)

CFLAGS += -std=c89 -Wall -Wextra -Wpedantic -g -I. -I$(API_DIR) -I$(INCLUDE_DIR)

HEADER_TAG = "$$(echo '$<' | sed -e 's/\(.*\)\.H/\U\1/' | sed -e 's/-/_/')_H"

all: $(TEMPLATES_OUT_H) $(TEMPLATES_OUT_C)

$(PP): %: %.c
	$(CC) $(CFLAGS) -o $@ $<

$(TEMPLATES_OUT_H): %.h: %.H $(PP)
	# Generating header
	@ echo "#ifndef $(HEADER_TAG)" > $@
	@ echo "#define $(HEADER_TAG)" >> $@
	cpp $(CFLAGS) -DGENCODECS_HEADER -nostdinc -P $< | $(PP) >> $@
	@ echo "#endif /* $(HEADER_TAG) */" >> $@
	# Formatting output with clang-format
	- clang-format -i $@
$(TEMPLATES_OUT_C): %.c: %.H $(PP)
	# Generating forward definitions
	@ echo "#include \"$*.h\"" > $@
	cpp $(CFLAGS) -DGENCODECS_FORWARD -nostdinc -P $< | $(PP) >> $@
	# Generating source
	cpp $(CFLAGS) -nostdinc -P $< | $(PP) >> $@
	# Formatting output with clang-format
	- clang-format -i $@

echo:
	@ echo 'TEMPLATES_OUT_H: $(TEMPLATES_OUT_H)'
	@ echo 'TEMPLATES_OUT_C: $(TEMPLATES_OUT_C)'

clean:
	rm -rf $(EXES) $(TEMPLATES_OUT_H) $(TEMPLATES_OUT_C) $(PP)

.PHONY : all clean
