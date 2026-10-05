CC = gcc
AR = ar

WARN     = -Wall -Wextra -Wconversion -pedantic
CFLAGS   = -std=c11 $(WARN) -O2
CPPFLAGS = -Iinclude -Isrc -MMD -MP

# make DEBUG=1 builds with AddressSanitizer and debug info
ifeq ($(DEBUG),1)
    CFLAGS = -std=c11 $(WARN) -g -fsanitize=address -fno-omit-frame-pointer
endif

SRC_DIR = src
BUILD   = build
LIB     = $(BUILD)/liblexer.a
DEMO    = $(BUILD)/demo

SRC = $(shell find $(SRC_DIR) -name '*.c')
OBJ = $(SRC:$(SRC_DIR)/%.c=$(BUILD)/%.o)

PREFIX ?= /usr/local

all: $(LIB)

$(LIB): $(OBJ)
	$(AR) rcs $@ $^

$(BUILD)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(DEMO): examples/demo.c $(LIB)
	$(CC) $(CPPFLAGS) $(CFLAGS) $< $(LIB) -o $@

demo: $(DEMO)

run: $(DEMO)
	./$(DEMO) examples/source.c

install: $(LIB)
	install -d $(PREFIX)/lib $(PREFIX)/include/lexer
	install -m 644 $(LIB) $(PREFIX)/lib
	install -m 644 include/lexer/*.h $(PREFIX)/include/lexer

clean:
	rm -rf $(BUILD)

-include $(OBJ:.o=.d)

.PHONY: all demo run install clean
