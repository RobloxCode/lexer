CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wconversion -pedantic -g \
         -fsanitize=address -fno-omit-frame-pointer

SRC = src/main.c \
	  utils/token_arr/token_arr.c \
	  utils/token/token.c \
	  utils/exp/exp.c \
	  utils/str_buf/str_buf.c \
	  utils/lexer/lexer.c \
	  utils/lexer/lexer_scan.c

OUT = bin/out

$(OUT): $(SRC)
	mkdir -p bin
	$(CC) $(CFLAGS) $^ -o $@

run: $(OUT)
	./$(OUT)

clean:
	rm -rf bin/

.PHONY: clean run
