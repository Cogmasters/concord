JSON_SRC=value.c parser.c snprintf.c tokenizer.c
JSON_HDR=json.h tokenizer.h utf8.h

HEADERS=stdlib.h string.h errno.h sys/types.h sys/stat.h unistd.h stdio.h

define json_amalgamation
	@echo "#ifndef ORCA_JSON_ONE" > $(1)
	@echo "#define ORCA_JSON_ONE" >> $(1)
	@echo "#define _GNU_SOURCE" >> $(1)
	@for ii in $(HEADERS); do echo '#include <'$$ii'>' >> $(1); done
	@echo "#include \"cee.h\"" >> $(1)
	@echo " " >> $(1)
	@for ii in $(JSON_HDR); do cat $$ii >> $(1); echo " " >> $(1); done
	@echo "#define ORCA_JSON_AMALGAMATION" > tmp.c
	@for ii in $(JSON_SRC); do echo '#include "'$$ii'"' >> tmp.c; done  
	$(CC) -E $(2) -nostdinc tmp.c >> $(1)
	@echo "#endif" >> $(1)
endef

.PHONY: release clean distclean

all: tester

json-one.c: $(JSON_SRC) cee.h
	$(call json_amalgamation, json-one.c)

json-one.o: json-one.c cee.h
	$(CC) -c json-one.c

cee.o: cee.c cee.h
	$(CC) -c -g cee.c

release: $(JSON_SRC)
	$(call json_amalgamation, json.c, -P)
	@mv json.c release
	@cp json.h release

tester: json-one.o cee.o
	$(CC) -std=c11 -static -g tester.c json-one.o cee.o

clean:
	rm -f a.c cee.o json-one.c json-one.o

distclean: clean
	rm -f cee.c cee.h