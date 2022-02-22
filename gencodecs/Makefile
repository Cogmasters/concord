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
DOCS_DIR     = $(TOP)/docs

# Main preprocessor input file
INP_PRE := discord-codecs.pre.h

# Single-files to be generated
OUT_C   := discord-codecs.c
OUT_H   := discord-codecs.h
OUT_O   := discord-codecs.o

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

all: $(OUT_O)

$(OUT_O): $(OUT_C) $(OUT_H)
	$(CC) -c $(CFLAGS) $< -o $@

.SUFFIXES: .c .o
.c.o:
	$(CC) -c $(CFLAGS) $< -o $@

$(PP): $(PPOBJ)
	$(CC) -o $(PP) $(PPOBJ)

HEADER_TAG = "$$(echo '$<' | sed -e 's/\(.*\)\.pre.h/\U\1/' | sed -e 's/-\|\//_/')_H"
$(OUT_H): $(INP_PRE) $(PP)
	@ echo "Generating headers"
	@ echo "#ifndef $(HEADER_TAG)" > $@
	@ echo "#define $(HEADER_TAG)" >> $@
	$(CPP) $(CFLAGS) -DGENCODECS_HEADER -nostdinc -P $(INP_PRE) | $(PP) >> $@
	@ echo "#endif /* $(HEADER_TAG) */" >> $@

$(OUT_C): $(INP_PRE) $(PP)
	@ echo "Generating forward definitions"
	@ echo "#include \"$(OUT_H)\"" > $(OUT_C)
	$(CPP) $(CFLAGS) -DGENCODECS_FORWARD -nostdinc -P $(INP_PRE) | $(PP) >> $(OUT_C)
	@ echo "Generating source"	
	$(CPP) $(CFLAGS) -nostdinc -P $(INP_PRE) | $(PP) >> $(OUT_C)

docs: $(HEADERS)

$(HEADERS): $(PP)

.SUFFIXES: .pre.h .h
.pre.h.h:
	@ echo "#ifndef $(HEADER_TAG)" > $(DOCS_DIR)/$@
	@ echo "#define $(HEADER_TAG)" >> $(DOCS_DIR)/$@
	$(CPP) $(CFLAGS) -DGENCODECS_HEADER -DGENCODECS_READ=\"$<\" -nostdinc -P $(INP_PRE) | $(PP) >> $(DOCS_DIR)/$@
	@ echo "#endif /* $(HEADER_TAG) */" >> $(DOCS_DIR)/$@

echo:
	@ echo 'HEADERS: $(HEADERS)'
	@ echo 'INP_PRE: $(INP_PRE)'
	@ echo 'OUT_H: $(OUT_H)'
	@ echo 'OUT_C: $(OUT_C)'
	@ echo 'OUT_O: $(OUT_O)'

.PHONY: clean docs

clean:
	rm -rf $(OUT_H) $(OUT_C) $(OUT_O) $(PP) $(PPOBJ) $(DOCS_DIR)/$(API_DIR)/*.h *.dSYM
