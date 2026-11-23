CFLAGS ?= -std=c17 -Wall -Wextra -Wpedantic -O2
DAYS := $(patsubst %/main.c,%,$(wildcard day[0-9][0-9]/main.c))

.PHONY: all
all: $(addprefix bin/,$(DAYS))

bin/%: %/main.c
	mkdir -p bin
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LDLIBS)
