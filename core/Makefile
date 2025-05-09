PREFIX = /usr/local

OBJS = cog-utils.o        \
       concord-error.o    \
       concord-notifier.o \
       concord-once.o     \
       io_poller.o        \
       user-agent.o       \
       websockets.o       \
       jsmn-find.o        \
       json-build.o       \
       logmod.o           \
       oa_hash.o          \
       priority_queue.o   \
       anomap.o           \
       threadpool.o       \
       queriec.o

CFLAGS += -std=c99 -pthread -D_XOPEN_SOURCE=600 -I. -I$(PREFIX)/include

all: $(OBJS)

echo:
	@ echo -e 'CC: $(CC)\n'
	@ echo -e 'CFLAGS: $(CFLAGS)\n'
	@ echo -e 'OBJS: $(OBJS)\n'

clean: 
	@ rm -f $(OBJS)

.PHONY: echo clean
