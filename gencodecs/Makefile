TOP = ../..
CC ?= gcc
PP := ./gencodecs-pp

INCLUDEDIR := $(TOP)/include
APIDIR     := api
OBJDIR     := $(TOP)/obj

TEMPLATES_IN    := discord-codecs.H
TEMPLATES_OUT_H := $(TEMPLATES_IN:%.H=%.h)
TEMPLATES_OUT_C := $(TEMPLATES_IN:%.H=%.c)

OBJS := $(OBJDIR)/jsmn-find.o $(OBJDIR)/json-build.o \
        $(TEMPLATES_OUT_C:%.c=$(OBJDIR)/%.o)

CFLAGS += -std=c89 -Wall -Wextra -Wpedantic -g -I. -I$(APIDIR) -I$(INCLUDEDIR)

HEADER_TAG = "$$(echo '$<' | sed -e 's/\(.*\)\.H/\U\1/' | sed -e 's/-/_/')_H"

all: $(PP) $(TEMPLATES_OUT_H) $(TEMPLATES_OUT_C)

$(PP): %: %.c
	$(CC) $(CFLAGS) -o $@ $<

$(TEMPLATES_OUT_H): %.h: %.H
	# Generating header
	@echo "#ifndef $(HEADER_TAG)" > $@
	@echo "#define $(HEADER_TAG)" >> $@
	cpp $(CFLAGS) -DGENCODECS_HEADER -nostdinc -P $< | $(PP) >> $@
	@echo "#endif /* $(HEADER_TAG) */" >> $@
	# Formatting output with clang-format
	clang-format -i $@
$(TEMPLATES_OUT_C): %.c: %.H
	# Generating source
	@echo "#include \"$*.h\"" > $@
	cpp $(CFLAGS) -nostdinc -P $< | $(PP) >> $@
	# Formatting output with clang-format
	clang-format -i $@

echo:
	@echo 'TEMPLATES_OUT_H: $(TEMPLATES_OUT_H)'
	@echo 'TEMPLATES_OUT_C: $(TEMPLATES_OUT_C)'

clean:
	rm -rf $(EXES) $(TEMPLATES_OUT_H) $(TEMPLATES_OUT_C) $(PP)

.PHONY : all clean
