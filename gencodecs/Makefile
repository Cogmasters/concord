# If you run into issues, change this to "cpp" instead of "cc -E"
# If you are cross-compiling, do NOT set this to the target preprocessor!
# This needs to run on the host -- that's why $(CC) and $(CPP) are
# available here to be set.
CC = cc
CPP = $(CC) -E
HOSTCC = cc

TOP = ..

API_DIR     = api
INCLUDE_DIR = $(TOP)/include
CORE_DIR    = $(TOP)/core
DOCS_DIR    = $(TOP)/docs

# Input file name without its extension
INPUT_NO_EXT = discord_codecs

# Input file to be preprocessed
INPUT = $(INPUT_NO_EXT).PRE.h
# Every spec the input pulls in; editing any of these must regenerate
SPECS = $(INPUT) gencodecs.h gencodecs-process.PRE.h all.PRE.h \
        $(wildcard $(API_DIR)/*.PRE.h) $(wildcard recipes/*.h)
# Resulting single-file amalgamations after preprocessing input file
OUT_C = $(INPUT_NO_EXT).c
OUT_H = $(INPUT_NO_EXT).h
OUT_O = $(INPUT_NO_EXT).o

# Generate individual headers for doxygen's parsing
HEADERS = $(API_DIR)/application.h           \
          $(API_DIR)/application_commands.h  \
          $(API_DIR)/audit_log.h             \
          $(API_DIR)/auto_moderation.h       \
          $(API_DIR)/channel.h               \
          $(API_DIR)/custom.h                \
          $(API_DIR)/emoji.h                 \
          $(API_DIR)/gateway.h               \
          $(API_DIR)/guild.h                 \
          $(API_DIR)/guild_scheduled_event.h \
          $(API_DIR)/guild_template.h        \
          $(API_DIR)/interactions.h          \
          $(API_DIR)/invite.h                \
          $(API_DIR)/message_components.h    \
          $(API_DIR)/oauth2.h                \
          $(API_DIR)/permissions.h           \
          $(API_DIR)/stage_instance.h        \
          $(API_DIR)/sticker.h               \
          $(API_DIR)/teams.h                 \
          $(API_DIR)/user.h                  \
          $(API_DIR)/voice.h                 \
          $(API_DIR)/voice_connections.h     \
          $(API_DIR)/webhook.h

LOCAL_CFLAGS = -O2
LOCAL_CFLAGS += -I. -I$(API_DIR) -I$(INCLUDE_DIR) -I$(CORE_DIR)
LOCAL_DFLAGS = -DGENCODECS_INIT -DGENCODECS_JSON_ENCODER -DGENCODECS_JSON_DECODER
LOCAL_CPPFLAGS = -nostdinc -P

# Convert 'foo/bar_baz.PRE.h' -> 'FOO_BAR_BAZ_H'
HEADER_TAG   = "$$(echo '$<' | sed -e 's/\(.*\)\.PRE.h/\1/' | sed -e 's/\//_/' | tr '[:lower:]' '[:upper:]')_H"
# Doxygen file description
DOXYGEN_DESC = "/**\n @file $@\n @author Cogmasters\n @brief Generated code\n*/"

all: $(OUT_O)

# Host codegen tool: target CFLAGS (sanitizers, -fPIC, cross flags) must
# not leak into a binary that only runs at build time
gencodecs-pp: gencodecs-pp.c
	$(HOSTCC) $(LOCAL_CFLAGS) gencodecs-pp.c -o gencodecs-pp

$(OUT_O): $(OUT_C) $(OUT_H)
	$(CC) -c $(CFLAGS) $(LOCAL_CFLAGS) $< -o $@
$(OUT_H): $(SPECS) gencodecs-pp
	@ echo "Generating header"
	@ echo "#ifndef $(HEADER_TAG)" > $@
	@ echo "#define $(HEADER_TAG)" >> $@
	$(CPP) $(CFLAGS) $(LOCAL_CFLAGS) -DGENCODECS_HEADER -DGENCODECS_DATA $(LOCAL_CPPFLAGS) $(INPUT) | ./gencodecs-pp >> $@
	$(CPP) $(CFLAGS) $(LOCAL_CFLAGS) $(LOCAL_DFLAGS) -DGENCODECS_HEADER $(LOCAL_CPPFLAGS) $(INPUT) | ./gencodecs-pp >> $@
	@ echo "#endif /* $(HEADER_TAG) */" >> $@
$(OUT_C): $(SPECS) gencodecs-pp
	@ echo "Generating forward definitions"
	@ echo "#include \"$(OUT_H)\"" > $(OUT_C)
	$(CPP) $(CFLAGS) $(LOCAL_CFLAGS) $(LOCAL_DFLAGS) -DGENCODECS_FORWARD -DGENCODECS_DATA $(LOCAL_CPPFLAGS) $(INPUT) | ./gencodecs-pp >> $(OUT_C)
	@ echo "Generating source"	
	$(CPP) $(CFLAGS) $(LOCAL_CFLAGS) $(LOCAL_DFLAGS) -DGENCODECS_DATA $(LOCAL_CPPFLAGS) $(INPUT) | ./gencodecs-pp >> $(OUT_C)

headers: $(HEADERS)

$(HEADERS): $(INPUT) gencodecs-pp

.SUFFIXES: .PRE.h .h
.PRE.h.h:
	@ echo $(DOXYGEN_DESC) > $(DOCS_DIR)/$@
	@ echo "#ifndef $(HEADER_TAG)" >> $(DOCS_DIR)/$@
	@ echo "#define $(HEADER_TAG)" >> $(DOCS_DIR)/$@
	$(CPP) $(CFLAGS) $(LOCAL_CFLAGS) -DGENCODECS_HEADER -DGENCODECS_DATA -DGENCODECS_READ=\"$<\" $(LOCAL_CPPFLAGS) -CC $(INPUT) | ./gencodecs-pp >> $(DOCS_DIR)/$@
	$(CPP) $(CFLAGS) $(LOCAL_CFLAGS) $(LOCAL_DFLAGS) -DGENCODECS_HEADER -DGENCODECS_READ=\"$<\" $(LOCAL_CPPFLAGS) $(INPUT) | ./gencodecs-pp >> $(DOCS_DIR)/$@
	@ echo "#endif /* $(HEADER_TAG) */" >> $(DOCS_DIR)/$@

echo:
	@ echo 'HEADERS: $(HEADERS)'
	@ echo 'INPUT: $(INPUT)'
	@ echo 'OUT_H: $(OUT_H)'
	@ echo 'OUT_C: $(OUT_C)'
	@ echo 'OUT_O: $(OUT_O)'

clean:
	@ rm -f $(OUT_H) $(OUT_C) $(OUT_O) gencodecs-pp $(DOCS_DIR)/$(API_DIR)/*.h

.PHONY: headers echo clean
