CC = gcc

CFLAGS = -std=c11 -Wall -Wextra -Wconversion -pedantic -g \
         -fsanitize=address -fno-omit-frame-pointer -Iinclude

SRC = test.c \
	  lexer/token_arr/token_arr.c \
	  lexer/token/token.c \
	  lexer/exp/exp.c \
	  lexer/str_buf/str_buf.c \
	  lexer/lexer/lexer.c \
	  lexer/lexer/lexer_scan.c \
	  lexer/alloc/alloc.c
OUT = test

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(OUT)

.PHONY: clean
