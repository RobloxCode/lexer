CC = gcc

ROOT      := ..
SRC_DIR   := $(ROOT)/src
BUILD_DIR := build

CPPFLAGS := -I$(ROOT)/include -I$(SRC_DIR) -I. -MMD -MP
CFLAGS   := -std=c11 -Wall -Wextra -Wpedantic -Wconversion -g \
            -fsanitize=address,undefined -fno-omit-frame-pointer
LDFLAGS  := -fsanitize=address,undefined

# Pass V=1 to also print every passing check.
ifeq ($(V),1)
    CPPFLAGS += -DTEST_VERBOSE
endif

# The tests compile the library sources directly (instead of linking
# build/liblexer.a) so they also have access to the internal headers and
# always run with the sanitizers enabled.
LIB_SRCS := $(shell find $(SRC_DIR) -name '*.c')
LIB_OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/lib/%.o,$(LIB_SRCS))

TEST_SRCS := $(wildcard test_*.c)
TESTS     := $(TEST_SRCS:%.c=$(BUILD_DIR)/%)

.PHONY: all test clean

all: $(TESTS)

test: $(TESTS)
	@failed=0; \
	for t in $(TESTS); do \
	    echo "==> $$t"; \
	    ./$$t || failed=1; \
	    echo; \
	done; \
	if [ $$failed -ne 0 ]; then echo "SOME TESTS FAILED"; exit 1; fi; \
	echo "ALL TEST FILES PASSED"

$(BUILD_DIR)/test_%: $(BUILD_DIR)/test_%.o $(LIB_OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/test_%.o: test_%.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/lib/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

-include $(wildcard $(BUILD_DIR)/*.d) $(shell find $(BUILD_DIR) -name '*.d' 2>/dev/null)
