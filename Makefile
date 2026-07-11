CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wconversion -pedantic -g \
         -fsanitize=address -fno-omit-frame-pointer

SRC = src/main.c src/lexer.c utils/token_arr.c utils/token.c utils/exp.c utils/str_slice.c
OUT = bin/out

$(OUT): $(SRC)
	mkdir -p bin
	$(CC) $(CFLAGS) $^ -o $@

run: $(OUT)
	./$(OUT)

clean:
	rm -rf bin/

.PHONY: clean run
