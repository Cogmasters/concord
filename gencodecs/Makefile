TOP = ..
CC  = cc

PP    := ./gencodecs-pp
PPOBJ := gencodecs-pp.o

# On some systems, "cpp" is the C++ compiler.
CPP = cc -E

API_DIR      = api
INCLUDE_DIR  = $(TOP)/include
COGUTILS_DIR = $(TOP)/cog-utils
CORE_DIR     = $(TOP)/core
THIRDP_DIR   = $(TOP)/core/third-party

INP_PRE := discord-codecs.pre.h
OUT_C   := discord-codecs.c
OUT_H   := discord-codecs.h
OUT_O   := discord-codecs.o

CFLAGS += -g -I. -I$(API_DIR) -I$(INCLUDE_DIR) -I$(COGUTILS_DIR) -I$(CORE_DIR) -I$(THIRDP_DIR)

HEADER_TAG = "$$(echo '$<' | sed -e 's/\(.*\)\.pre.h/\U\1/' | sed -e 's/-/_/')_H"

all: $(OUT_O)

$(OUT_O): $(OUT_C) $(OUT_H)
	$(CC) -c $(CFLAGS) $< -o $@

.SUFFIXES: .c .o
.c.o:
	$(CC) -c $(CFLAGS) $< -o $@

all: $(OUT_H) $(OUT_C)

$(PP): $(PPOBJ)
	$(CC) -o $(PP) $(PPOBJ)

$(OUT_H): $(INP_PRE) $(PP)
	@ echo "Generating headers"
	@ echo "#ifndef $(HEADER_TAG)" > $(OUT_H)
	@ echo "#define $(HEADER_TAG)" >> $(OUT_H)
	$(CPP) $(CFLAGS) -DGENCODECS_HEADER -nostdinc -P $(INP_PRE) | $(PP) >> $(OUT_H)
	@ echo "#endif /* $(HEADER_TAG) */" >> $(OUT_H)

$(OUT_C): $(INP_PRE) $(PP)
	@ echo "Generating forward definitions"
	@ echo "#include \"$(OUT_H)\"" > $(OUT_C)
	$(CPP) $(CFLAGS) -DGENCODECS_FORWARD -nostdinc -P $(INP_PRE) | $(PP) >> $(OUT_C)
	# Generating source
	$(CPP) $(CFLAGS) -nostdinc -P $(INP_PRE) | $(PP) >> $(OUT_C)

echo:
	@ echo 'INP_PRE: $(INP_PRE)'
	@ echo 'OUT_H: $(OUT_H)'
	@ echo 'OUT_C: $(OUT_C)'
	@ echo 'OUT_O: $(OUT_O)'

.PHONY: clean

clean:
	rm -rf $(OUT_H) $(OUT_C) $(OUT_O) $(PP) $(PPOBJ) *.dSYM
