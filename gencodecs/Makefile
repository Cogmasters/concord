TOP = ..
CC  = cc

PP    := ./gencodecs-pp
PPOBJ := gencodecs-pp.o

API_DIR      = api
INCLUDE_DIR  = $(TOP)/include
COGUTILS_DIR = $(TOP)/cog-utils
CORE_DIR     = $(TOP)/core
THIRDP_DIR   = $(TOP)/core/third-party
DOCS_DIR     = $(TOP)/docs

# Main preprocessor input file
INP_PRE := discord_codecs.pre.h

# Single-files to be generated
OUT_C   := discord_codecs.c
OUT_H   := discord_codecs.h
OUT_O   := discord_codecs.o

# Generate individual headers, useful for docs generation
HEADERS = $(API_DIR)/application.h \
          $(API_DIR)/application_commands.h \
          $(API_DIR)/audit_log.h \
          $(API_DIR)/channel.h \
          $(API_DIR)/custom.h \
          $(API_DIR)/emoji.h \
          $(API_DIR)/gateway.h \
          $(API_DIR)/guild.h \
          $(API_DIR)/guild_scheduled_event.h \
          $(API_DIR)/guild_template.h \
          $(API_DIR)/interactions.h \
          $(API_DIR)/invite.h \
          $(API_DIR)/message_components.h \
          $(API_DIR)/permissions.h \
          $(API_DIR)/stage_instance.h \
          $(API_DIR)/sticker.h \
          $(API_DIR)/teams.h \
          $(API_DIR)/user.h \
          $(API_DIR)/voice.h \
          $(API_DIR)/voice_connections.h \
          $(API_DIR)/webhook.h

CFLAGS += -g -I. -I$(API_DIR) -I$(INCLUDE_DIR) -I$(COGUTILS_DIR) -I$(CORE_DIR) -I$(THIRDP_DIR)
DFLAGS += -DGENCODECS_INIT -DGENCODECS_JSON_ENCODER -DGENCODECS_JSON_DECODER

# Convert 'folder/hello_world.pre.h' -> 'FOLDER_HELLO_WORLD_H'
HEADER_TAG   = "$$(echo '$<' | sed -e 's/\(.*\)\.pre.h/\1/' | sed -e 's/\//_/' | tr '[:lower:]' '[:upper:]')_H"
# Doxygen file description
DOXYGEN_DESC = "/**\n @file $@\n @author Cogmasters\n @brief Generated code\n*/"

all: $(OUT_O)

$(OUT_O): $(OUT_C) $(OUT_H)
	$(CC) -c $(CFLAGS) $< -o $@

.SUFFIXES: .c .o
.c.o:
	$(CC) -c $(CFLAGS) $< -o $@

$(PP): $(PPOBJ)
	$(CC) -o $(PP) $(PPOBJ)

$(OUT_H): $(INP_PRE) $(PP)
	@ echo "Generating header"
	@ echo "#ifndef $(HEADER_TAG)" > $@
	@ echo "#define $(HEADER_TAG)" >> $@
	$(CPP) $(CFLAGS) -DGENCODECS_HEADER -DGENCODECS_DATA -nostdinc -P $(INP_PRE) | $(PP) >> $@
	$(CPP) $(CFLAGS) -DGENCODECS_HEADER $(DFLAGS) -nostdinc -P $(INP_PRE) | $(PP) >> $@
	@ echo "#endif /* $(HEADER_TAG) */" >> $@

$(OUT_C): $(INP_PRE) $(PP)
	@ echo "Generating forward definitions"
	@ echo "#include \"$(OUT_H)\"" > $(OUT_C)
	$(CPP) $(CFLAGS) -DGENCODECS_FORWARD -DGENCODECS_DATA $(DFLAGS) -nostdinc -P $(INP_PRE) | $(PP) >> $(OUT_C)
	@ echo "Generating source"	
	$(CPP) $(CFLAGS) -DGENCODECS_DATA $(DFLAGS) -nostdinc -P $(INP_PRE) | $(PP) >> $(OUT_C)

docs: $(HEADERS)

$(HEADERS): $(PP)

.SUFFIXES: .pre.h .h
.pre.h.h:
	@ echo $(DOXYGEN_DESC) > $(DOCS_DIR)/$@
	@ echo "#ifndef $(HEADER_TAG)" >> $(DOCS_DIR)/$@
	@ echo "#define $(HEADER_TAG)" >> $(DOCS_DIR)/$@
	$(CPP) $(CFLAGS) -DGENCODECS_HEADER -DGENCODECS_DATA -DGENCODECS_READ=\"$<\"-nostdinc -P -CC $(INP_PRE) | $(PP) >> $(DOCS_DIR)/$@
	$(CPP) $(CFLAGS) -DGENCODECS_HEADER -DGENCODECS_READ=\"$<\" $(DFLAGS) -nostdinc -P $(INP_PRE) | $(PP) >> $(DOCS_DIR)/$@
	@ echo "#endif /* $(HEADER_TAG) */" >> $(DOCS_DIR)/$@

echo:
	@ echo 'HEADERS: $(HEADERS)'
	@ echo 'INP_PRE: $(INP_PRE)'
	@ echo 'OUT_H: $(OUT_H)'
	@ echo 'OUT_C: $(OUT_C)'
	@ echo 'OUT_O: $(OUT_O)'

clean:
	@ $(RM) $(OUT_H) $(OUT_C) $(OUT_O) $(PP) $(PPOBJ) $(DOCS_DIR)/$(API_DIR)/*.h *.dSYM

.PHONY: clean docs
