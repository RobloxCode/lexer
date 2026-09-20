CC = gcc
ROOT := $(abspath $(dir $(lastword $(MAKEFILE_LIST)))/../../..)

CFLAGS = -std=c11 -Wall -Wextra -Wconversion -pedantic -g \
         -fsanitize=address -fno-omit-frame-pointer \
         -I$(ROOT)/include

# every .c in src/ except main.c (the test has its own main)
LIB_SRC = $(filter-out $(ROOT)/src/main.c, $(shell find $(ROOT)/src -name '*.c'))
SRC = test.c $(LIB_SRC)
HDRS = $(shell find $(ROOT)/include -name '*.h')
OUT = test

$(OUT): $(SRC) $(HDRS)
	$(CC) $(CFLAGS) $(SRC) -o $@

run: $(OUT)
	./$(OUT)

clean:
	rm -f $(OUT)

.PHONY: run clean
