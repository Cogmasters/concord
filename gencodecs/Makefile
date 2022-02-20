TOP = ../..
CC = cc
PP := ./gencodecs-pp
PPOBJ := gencodecs-pp.o

# On some systems, "cpp" is the C++ compiler.
CPP = cc -E

INCLUDE_DIR = $(TOP)/include
API_DIR = api
OBJ_DIR = $(TOP)/obj

TEMPLATES_IN    := discord-codecs.pre.h
TEMPLATES_OUT_C := discord-codecs.c
TEMPLATES_OUT_H := discord-codecs.h

CFLAGS += -g -I. -I$(API_DIR) -I$(INCLUDE_DIR)

HEADER_TAG = "$$(echo '$<' | sed -e 's/\(.*\)\.pre.h/\U\1/' | sed -e 's/-/_/')_H"

all: $(TEMPLATES_OUT_H) $(TEMPLATES_OUT_C)

.SUFFIXES: .c .o
.c.o:
	$(CC) -c $(CFLAGS) $< -o $@

all: $(TEMPLATES_OUT_H) $(TEMPLATES_OUT_C)

$(PP): $(PPOBJ)
	$(CC) -o $(PP) $(PPOBJ)

$(TEMPLATES_OUT_H): $(TEMPLATES_IN) $(PP)
	@ echo "Generating headers"
	@ echo "#ifndef $(HEADER_TAG)" > discord-codecs.h
	@ echo "#define $(HEADER_TAG)" >> discord-codecs.h
	$(CPP) $(CFLAGS) -DGENCODECS_HEADER -nostdinc -P discord-codecs.pre.h | $(PP) >> discord-codecs.h
	@ echo "#endif /* $(HEADER_TAG) */" >> discord-codecs.h

$(TEMPLATES_OUT_C): $(TEMPLATES_IN) $(PP)
	@ echo "Generating forward definitions"
	@ echo "#include \"discord-codecs.h\"" > discord-codecs.c
	$(CPP) $(CFLAGS) -DGENCODECS_FORWARD -nostdinc -P discord-codecs.pre.h | $(PP) >> discord-codecs.c
	# Generating source
	$(CPP) $(CFLAGS) -nostdinc -P discord-codecs.pre.h | $(PP) >> discord-codecs.c

echo:
	@ echo 'TEMPLATES_OUT_H: $(TEMPLATES_OUT_H)'
	@ echo 'TEMPLATES_OUT_C: $(TEMPLATES_OUT_C)'

.PHONY: clean

clean:
	rm -rf $(TEMPLATES_OUT_H) $(TEMPLATES_OUT_C) $(PP) $(PPOBJ) *.dSYM
