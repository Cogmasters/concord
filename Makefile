PREFIX ?= /usr/local
SHELL  := /bin/bash

CC     ?= gcc
OBJDIR := obj
LIBDIR := lib

# common/utils
CEE_UTILS_DIR  := cee-utils
CEE_UTILS_SRC  := $(wildcard $(CEE_UTILS_DIR)/*.c) 
CEE_UTILS_OBJS := $(CEE_UTILS_SRC:%=$(OBJDIR)/%.o)

COMMON_DIR  := common
COMMON_SRC  := $(wildcard $(COMMON_DIR)/*.c) $(wildcard $(COMMON_DIR)/**/*.c)
COMMON_OBJS := $(COMMON_SRC:%=$(OBJDIR)/%.o)

# Specs
SPECSDIR     := specs-code
SPECS        := $(sort $(wildcard specs/*/*.json))
SPECS_SUBDIR := $(sort $(patsubst specs/%, %, $(dir $(SPECS))))

# APIs objs
DISCORD_SRC  := $(wildcard discord-*.c $(SPECSDIR)/discord/*.c)
DISCORD_OBJS := $(DISCORD_SRC:%=$(OBJDIR)/%.o)
REDDIT_SRC   := $(wildcard reddit-*.c $(SPECSDIR)/reddit/*.c)
REDDIT_OBJS  := $(REDDIT_SRC:%=$(OBJDIR)/%.o)
GITHUB_SRC   := $(wildcard github-*.c)
GITHUB_OBJS  := $(GITHUB_SRC:%=$(OBJDIR)/%.o)

# API libs cflags
LIBDISCORD_CFLAGS :=
LIBGITHUB_CFLAG   :=
LIBREDDIT_CFLAGS  :=

# API libs ldflags
LIBDISCORD_LDFLAGS := -ldiscord
LIBGITHUB_LDFLAGS  := -lgithub
LIBREDDIT_LDFLAGS  := -lreddit

# API libs
LIBDISCORD := $(LIBADDONS) $(LIBDIR)/libdiscord.a
LIBGITHUB  := $(LIBADDONS) $(LIBDIR)/libgithub.a
LIBREDDIT  := $(LIBADDONS) $(LIBDIR)/libreddit.a

# Code generator
SPECSGEN_CC     ?= gcc
SPECSGEN_OBJDIR := specs_obj
SPECSGEN_SRC    := $(CEE_UTILS_DIR)/cee-utils.c   \
                   $(CEE_UTILS_DIR)/json-actor.c  \
                   $(CEE_UTILS_DIR)/ntl.c         \
                   $(CEE_UTILS_DIR)/json-string.c \
                   $(CEE_UTILS_DIR)/json-scanf.c  \
                   $(CEE_UTILS_DIR)/json-struct.c \
                   $(CEE_UTILS_DIR)/json-printf.c \
                   $(CEE_UTILS_DIR)/log.c         \
                   specs/specs-gen.c
SPECSGEN_OBJS   := $(SPECSGEN_SRC:%=$(SPECSGEN_OBJDIR)/%.o)

BOTS_DIR   := bots
BOTS_SRC   := $(wildcard $(BOTS_DIR)/bot-*.c)
BOTS_EXES  := $(patsubst %.c, %.exe, $(BOTS_SRC))

BOTX_DIR  := botx
BOTX_SRC  := $(wildcard $(BOTX_DIR)/bot-*.c)
BOTX_EXES := $(patsubst %.c, %.bx, $(BOTX_SRC))

TEST_DIR  := test
TEST_SRC  := $(wildcard $(TEST_DIR)/test-*.c)
TEST_EXES := $(filter %.exe, $(TEST_SRC:.c=.exe))


LIBS_CFLAGS  += -I./mujs
LIBS_LDFLAGS += -L./$(LIBDIR) -lpthread -lm

CFLAGS += -std=c11 -O0 -g                                 \
          -Wall -Wno-unused-function                      \
          -I. -I./$(CEE_UTILS_DIR)                        \
					-I./$(COMMON_DIR) -I./$(COMMON_DIR)/third-party \
          -DLOG_USE_COLOR

ifeq ($(addons),1)
	# prepare addon flags
	ADDONS_SRC      := $(wildcard add-ons/*.c)
	ADDONS_OBJS     := $(ADDONS_SRC:%=$(OBJDIR)/%.o)
	ADDONS_BOTS_SRC := $(wildcard add-ons/*_bots/*.c)
	LIBADDONS       := $(LIBDIR)/libaddons.a

	# include addon flags
	BOTS_EXES    += $(ADDONS_BOTS_SRC:%.c=%.exe)
	LIBS_LDFLAGS += -laddons
	CFLAGS       += -I./add-ons
endif

ifeq ($(BEARSSL),1)
	LIBS_LDFLAGS += -lbearssl -static
	CFLAGS += -DBEARSSL
else ifneq (,$(findstring $(CC),stensal-c sfc)) # ifeq stensal-c OR sfc
	LIBS_LDFLAGS += -lcurl-bearssl -lbearssl -static
	CFLAGS += -DBEARSSL
else
	LIBS_LDFLAGS += $(pkg-config --libs --cflags libcurl) -lcurl -lcrypto
	CFLAGS += -Wno-unused-but-set-variable
endif

ifeq ($(static_debug),1)
	CFLAGS +=  -D_STATIC_DEBUG
else ifeq ($(static_debug),2) 
	CFLAGS +=  -D_STRICT_STATIC_DEBUG
else ifeq ($(static_debug),3) 
	CFLAGS +=  -D_STATIC_DEBUG -D_STRICT_STATIC_DEBUG
endif

ifneq (,$(findstring $(CC),stensal-c sfc)) # ifeq stensal-c OR sfc
	CFLAGS += -D_DEFAULT_SOURCE
	__D    := $(shell dirname $(shell which $(CC)))
	__DEST := $(patsubst %/stensal/bin,%,$(__D))
	PREFIX := $(__DEST)/usr
else
	CFLAGS += -fPIC -D_XOPEN_SOURCE=700
endif


#generic compilation
$(SPECSGEN_OBJDIR)/%.c.o : %.c
	$(SPECSGEN_CC) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $<
$(OBJDIR)/%.c.o : %.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -c -o $@ $<
$(BOTS_DIR)/%.exe: $(BOTS_DIR)/%.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -o $@ $< $(LIBDISCORD_LDFLAGS) $(LIBREDDIT_LDFLAGS) $(LIBGITHUB_LDFLAGS) $(LIBS_LDFLAGS)
%.exe: %.c all_api_libs
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -o $@ $< $(LIBDISCORD_LDFLAGS) $(LIBREDDIT_LDFLAGS) $(LIBGITHUB_LDFLAGS) -lmujs -lsqlite3 $(LIBS_LDFLAGS)
%.bx: %.c mujs all_api_libs
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -o $@ $< $(LIBDISCORD_LDFLAGS) -lmujs -lsqlite3 $(LIBS_LDFLAGS)
%.bz:%.c
	$(CC) $(CFLAGS) $(LIBS_CFLAGS) -o $@ $< $(LIBS_LDFLAGS) 


all: discord reddit github
test: discord reddit github mujs $(TEST_EXES)

botx:
	@ $(MAKE) addons=1 all mujs all_api_libs
	@ $(MAKE) addons=1 $(BOTX_EXES)

discord: common $(DISCORD_OBJS) $(LIBDISCORD)
reddit: common $(REDDIT_OBJS) $(LIBREDDIT)
github: common $(GITHUB_OBJS) $(LIBGITHUB)

common: cee_utils $(COMMON_OBJS)
cee_utils: $(CEE_UTILS_OBJS) | $(CEE_UTILS_DIR)

specs: $(SPECS_OBJS)

$(CEE_UTILS_OBJS): | $(OBJDIR)
$(COMMON_OBJS): | $(OBJDIR)
$(DISCORD_OBJS): | $(OBJDIR)
$(REDDIT_OBJS): | $(OBJDIR)
$(GITHUB_OBJS): | $(OBJDIR)
$(SPECS_OBJS): | $(OBJDIR)
$(SPECSGEN_OBJS): | $(SPECSGEN_OBJDIR)

echo:
	@ echo CC: $(CC)
	@ echo PREFIX: $(PREFIX)
	@ echo BOTS_EXES: $(BOTS_EXES)
	@ echo SPECS: $(SPECS)
	@ echo SPECS_OBJS: $(SPECS_OBJS)
	@ echo SPECS_SUBDIR: $(SPECS_SUBDIR)

specs_gen: cee_utils | $(SPECS_OBJS)
	@ $(MAKE) clean specs_clean clean_specs_gen all_headers specs

bots:
	@ $(MAKE) all
	@ $(MAKE) $(BOTS_EXES)

$(CEE_UTILS_DIR):
	if [[ ! -d $@ ]]; then        \
	  ./scripts/get-cee-utils.sh; \
	fi

$(OBJDIR) :
	mkdir -p $(OBJDIR)/$(CEE_UTILS_DIR)                                                                      \
	         $(OBJDIR)/$(COMMON_DIR)/third-party                                                             \
	         $(addprefix $(SPECSDIR)/, $(SPECS_SUBDIR)) $(addprefix $(OBJDIR)/$(SPECSDIR)/, $(SPECS_SUBDIR)) \
	         $(OBJDIR)/$(TEST_DIR)                                                                           \
	         $(OBJDIR)/add-ons

$(SPECSGEN_OBJDIR) : | $(OBJDIR)
	mkdir -p $(SPECSGEN_OBJDIR)/$(CEE_UTILS_DIR)          \
	         $(SPECSGEN_OBJDIR)/$(COMMON_DIR)/third-party \
	         $(SPECSGEN_OBJDIR)/specs

$(LIBDIR) :
	mkdir -p $(LIBDIR)

all_headers: specs-gen.exe
	rm -rf $(SPECSDIR)/*/all_*
	$(foreach var, $(SPECS),./bin/specs-gen.exe -S -a -o $(patsubst specs/%, $(SPECSDIR)/%, $(dir $(var))all_structs.h) $(var);)
	$(foreach var, $(SPECS),./bin/specs-gen.exe -E -a -o $(patsubst specs/%, $(SPECSDIR)/%, $(dir $(var))all_enums.h) $(var);)
	$(foreach var, $(SPECS),./bin/specs-gen.exe -F -a -o $(patsubst specs/%, $(SPECSDIR)/%, $(dir $(var))all_functions.h) $(var);)
	$(foreach var, $(SPECS),./bin/specs-gen.exe -O -a -o $(patsubst specs/%, $(SPECSDIR)/%, $(dir $(var))all_opaque_struct.h) $(var);)
	$(foreach var, $(SPECS),./bin/specs-gen.exe -c -o $(patsubst specs/%, $(SPECSDIR)/%, $(var:%.json=%.c)) $(var);)
	$(foreach var, $(SPECS),./bin/specs-gen.exe -d -o $(patsubst specs/%, $(SPECSDIR)/%, $(var:%.json=%.h)) $(var);)

specs-gen.exe: $(SPECSGEN_OBJS) | $(SPECSGEN_OBJDIR)
	$(SPECSGEN_CC) -o $@ $(SPECSGEN_OBJS) -lm
	mkdir -p bin
	mv $@ ./bin

all_api_libs : $(LIBDISCORD) $(LIBGITHUB) $(LIBREDDIT) $(LIBADDONS)

# API libraries compilation
$(LIBDISCORD) : $(CEE_UTILS_OBJS) $(COMMON_OBJS) $(DISCORD_OBJS) | $(LIBDIR)
	$(AR) -cvq $@ $^
$(LIBGITHUB) : $(CEE_UTILS_OBJS) $(COMMON_OBJS) $(GITHUB_OBJS) | $(LIBDIR)
	$(AR) -cvq $@ $^
$(LIBREDDIT) : $(CEE_UTILS_OBJS) $(COMMON_OBJS) $(REDDIT_OBJS) | $(LIBDIR)
	$(AR) -cvq $@ $^
$(LIBADDONS) : $(CEE_UTILS_OBJS) $(COMMON_OBJS) $(ADDONS_OBJS) | $(LIBDIR)
	$(AR) -cvq $@ $^

mujs:
	$(MAKE) -C mujs
	mkdir -p $(LIBDIR)
	cp mujs/build/release/libmujs.a $(LIBDIR)

install :
	mkdir -p $(PREFIX)/lib/
	mkdir -p $(PREFIX)/include/orca
	install -d $(PREFIX)/lib/
	install -m 644 $(LIBDISCORD) $(PREFIX)/lib/
	install -d $(PREFIX)/include/orca/
	install -m 644 *.h $(CEE_UTILS_DIR)/*.h $(COMMON_DIR)/*.h $(COMMON_DIR)/**/*.h $(PREFIX)/include/orca/
	install -d $(PREFIX)/include/orca/$(SPECSDIR)/discord/
	install -m 644 $(SPECSDIR)/discord/*.h $(PREFIX)/include/orca/$(SPECSDIR)/discord/

specs_clean :
	rm -rf $(SPECSDIR)
clean_specs_gen:
	rm -rf $(SPECSGEN_OBJDIR) bin/*
clean : 
	rm -rf $(OBJDIR) *.exe $(TEST_DIR)/*.exe $(BOTS_DIR)/*.exe
	rm -rf $(BOTX_DIR)/*.bx
	$(MAKE) -C mujs clean
	rm -rf $(LIBDIR)
purge : clean
	rm -rf $(LIBDIR)
	rm -rf $(SPECSGEN_OBJDIR)
	rm -rf $(CEE_UTILS_DIR)

.PHONY : all install clean purge mujs bots botx
.ONESHELL:
