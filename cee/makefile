CEE_SRC=cee-common.c box.c str.c dict.c map.c set.c stack.c tuple.c triple.c \
  quadruple.c vect.c tagged.c singleton.c closure.c block.c n_tuple.c

HEADERS=stdio.h string.h stdlib.h stdarg.h search.h assert.h errno.h

define cee_amalgamation
	@echo "#define CEE_AMALGAMATION" > tmp.c
	@for ii in $(CEE_SRC); do echo '#include "'$$ii'"' >> tmp.c; done
	@echo "#ifndef CEE_ONE" > $(1)
	@echo "#define CEE_ONE" >> $(1)
	@echo "#define _GNU_SOURCE" >> $(1)
	@for ii in $(HEADERS); do echo '#include <'$$ii'>' >> $(1); done
	@cat cee.h >> $(1)
	@echo " " >> $(1)
	@cat cee-internal.h >> $(1)
	$(CC) -E $(2) -nostdinc tmp.c >> $(1)
	@echo "#endif" >> $(1)
endef

all: tester

cee-one.c: $(CEE_SRC)
	$(call cee_amalgamation, cee-one.c)

cee-one.o: cee-one.c
	$(CC) -c -g cee-one.c


release: $(CEE_SRC)
	$(call cee_amalgamation, cee.c,-P)
	@mv cee.c  release
	@cp cee.h  release

tester: cee-one.o
	$(CC) -static -g tester.c cee-one.o

clean:
	rm -f cee.c tmp.c cee-one.* a.out