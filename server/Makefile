CC = gcc
BUILD_DIR ?= ./build
SRC_DIR ?= ./src
TARGET_EXEC ?= convoy
SRCS := $(shell find $(SRC_DIR) -name *.c)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

all: $(BUILD_DIR)/$(TARGET_EXEC)

test: CPPFLAGS += -D TESTING
test: all

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@

$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJS): FORCE
FORCE:

.PHONY: clean

clean:
	rm -r $(BUILD_DIR)

MKDIR_P ?= mkdir -p