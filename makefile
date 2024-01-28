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

ca65-symbls-to-nl.out: main.c
	@echo Compiling $@
	@$(CC) $(CFLAGS) ./main.c -o ca65-symbls-to-nl.out $(LIBS)

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM *.nl