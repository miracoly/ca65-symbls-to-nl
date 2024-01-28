###
CFLAGS  = -std=c17
CFLAGS += -g
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -pedantic
CFLAGS += -Werror
CFLAGS += -Wmissing-declarations
CFLAGS += -DUNITY_SUPPORT_64 -DUNITY_OUTPUT_COLOR

#LIBS =

.PHONY: all
all: ca65-symbls-to-nl.out

.PHONY: install
install: ca65-symbls-to-nl.out
	@mkdir -p $(DESTDIR)/bin
	@cp ca65-symbls-to-nl.out $(DESTDIR)/bin/ca65-symbols-to-nl

ca65-symbls-to-nl.out: main.c
	@echo Compiling $@
	@$(CC) $(CFLAGS) ./main.c -o ca65-symbls-to-nl.out $(LIBS)

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM *.nl