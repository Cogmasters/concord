CC ?= gcc

CORE_DIR   = .
THIRDP_DIR = third-party

OBJS = cog-utils.o                    \
       io_poller.o                    \
       user-agent.o                   \
       websockets.o                   \
       $(THIRDP_DIR)/curl-websocket.o \
       $(THIRDP_DIR)/jsmn-find.o      \
       $(THIRDP_DIR)/json-build.o     \
       $(THIRDP_DIR)/log.o            \
       $(THIRDP_DIR)/logconf.o        \
       $(THIRDP_DIR)/priority_queue.o \
       $(THIRDP_DIR)/sha1.o           \
       $(THIRDP_DIR)/threadpool.o

WFLAGS += -Wall -Wextra -Wpedantic
CFLAGS += -std=c99 -O0 -g -pthread -D_XOPEN_SOURCE=600 -DLOG_USE_COLOR \
          -I$(CORE_DIR) -I$(THIRDP_DIR) # $(WFLAGS)

all: $(OBJS)

echo:
	@ echo -e 'CC: $(CC)\n'
	@ echo -e 'OBJS: $(OBJS)\n'

clean: 
	@ $(RM) $(OBJS)

.PHONY: echo clean
