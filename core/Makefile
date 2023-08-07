PREFIX = /usr/local

OBJS = cog-utils.o      \
       io_poller.o      \
       user-agent.o     \
       websockets.o     \
       curl-websocket.o \
       jsmn-find.o      \
       json-build.o     \
       log.o            \
       logconf.o        \
       priority_queue.o \
       anomap.o         \
       sha1.o           \
       threadpool.o     \
       queriec.o

WFLAGS  = -Wall -Wextra -Wpedantic
CFLAGS += -std=c99 -pthread -D_XOPEN_SOURCE=600 -DLOG_USE_COLOR \
          -I. -I$(PREFIX)/include # $(WFLAGS)

all: $(OBJS)

echo:
	@ echo 'CC: $(CC)'
	@ echo 'CFLAGS: $(CFLAGS)'
	@ echo 'OBJS: $(OBJS)'

clean:
	@ rm -f $(OBJS)

.PHONY: echo clean
