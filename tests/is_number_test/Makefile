CC = gcc

CFLAGS = -std=c11 -Wall -Wextra -Wconversion -pedantic -g \
         -fsanitize=address -fno-omit-frame-pointer

SRC = test.c \
	  ../../utils/token_arr/token_arr.c \
	  ../../utils/token/token.c \
	  ../../utils/exp/exp.c \
	  ../../utils/str_buf/str_buf.c \
	  ../../utils/lexer/lexer.c \
	  ../../utils/lexer/lexer_scan.c \
	  ../../utils/alloc/alloc.c
OUT = test

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(OUT)

.PHONY: clean
