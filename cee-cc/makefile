CEE_SRC=cee-common.cc box.cc str.cc dict.cc map.cc set.cc stack.cc tuple.cc triple.cc \
  quadruple.cc vect.cc tagged.cc singleton.cc closure.cc block.cc n_tuple.cc

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
	$(CXX) -E $(2) -nostdinc tmp.c >> $(1)
	@echo "#endif" >> $(1)
endef

.PHONY: release clean distclean

all: tester

cee-one.cc: $(CEE_SRC)
	$(call cee_amalgamation, cee-one.cc)

cee-one.o: cee-one.cc
	$(CXX) -c -g cee-one.cc


release:
	$(call cee_amalgamation, cee.cc,-P)
	@mv cee.cc  release
	@cp cee.h  release

tester: cee-one.o
	$(CXX) -static -g tester.cc cee-one.o

clean:
	rm -f cee.cc tmp.cc cee-one.* a.out