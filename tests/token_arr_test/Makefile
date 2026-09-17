CC = gcc

CFLAGS = -std=c11 -Wall -Wextra -Wconversion -pedantic -g \
         -fsanitize=address -fno-omit-frame-pointer -Iinclude

SRC = test.c ../../src/token_arr/token_arr.c
OUT = test

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(OUT)

.PHONY: clean
