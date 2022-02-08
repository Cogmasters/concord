TOP = ../..
CC ?= gcc

INCLUDEDIR := $(TOP)/include
OBJDIR     := $(TOP)/obj

TEMPLATES_IN    := discord.H
TEMPLATES_OUT_H := $(TEMPLATES_IN:%.H=%.h)
TEMPLATES_OUT_C := $(TEMPLATES_IN:%.H=%.c)

OBJS := $(OBJDIR)/jsmn-find.o $(OBJDIR)/json-build.o \
        $(TEMPLATES_OUT_C:%.c=$(OBJDIR)/%.o)

CFLAGS += -std=c89 -Wall -Wextra -Wpedantic -g -I. -I.. -I$(INCLUDEDIR)

GENSOURCE_FLAGS := -DGENCODECS_STRUCT \
                   -DGENCODECS_STRUCT_INIT \
                   -DGENCODECS_STRUCT_JSON_ENCODER \
                   -DGENCODECS_STRUCT_JSON_DECODER

HEADER_TAG = "$$(echo '$<' | sed -e 's/\(.*\)\.H/\U\1/')_H"

all: $(TEMPLATES_OUT_H) $(TEMPLATES_OUT_C)

$(TEMPLATES_OUT_H): %.h: %.H
	# Generating header
	@echo "#ifndef $(HEADER_TAG)" > $@
	@echo "#define $(HEADER_TAG)" >> $@
	cpp $(CFLAGS) -DGENCODECS_HEADER $(GENSOURCE_FLAGS) -nostdinc -CC -P $< | sed -e 's/GENCODECS_DIRECTIVE(\(.*\))/#\1/' >> $@
	@echo "#endif /* $(HEADER_TAG) */" >> $@
$(TEMPLATES_OUT_C): %.c: %.H
	# Generating source
	@echo "#include \"$*.h\"" > $@
	cpp $(CFLAGS) $(GENSOURCE_FLAGS) -nostdinc -P $< | sed -e 's/GENCODECS_DIRECTIVE(\(.*\))/#\1/' >> $@

echo:
	@echo 'TEMPLATES_OUT_H: $(TEMPLATES_OUT_H)'
	@echo 'TEMPLATES_OUT_C: $(TEMPLATES_OUT_C)'

clean:
	rm -rf $(EXES) $(TEMPLATES_OUT_H) $(TEMPLATES_OUT_C)

.PHONY : all clean
