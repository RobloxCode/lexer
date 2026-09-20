CC = gcc

CFLAGS = -std=c11 -Wall -Wextra -Wconversion -pedantic -g \
         -fsanitize=address -fno-omit-frame-pointer

SRC = test.c \
	  src/token_arr/token_arr.c \
	  src/utils/token/token.c \
	  scr/utils/exp/exp.c \
	  scr/utils/str_buf/str_buf.c \
	  scr/utils/lexer/lexer.c \
	  scr/utils/lexer/lexer_scan.c \
	  scr/utils/alloc/alloc.c
OUT = test

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(OUT)

.PHONY: clean
