CC = gcc
BUILD_DIR ?= ./build
SRC_DIR ?= ./src
TARGET_EXEC ?= convoy
SRCS := $(shell find $(SRC_DIR) -name *.c)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
TEST = NO_TEST
CPPFLAGS += -D $(TEST)
LDFLAGS += -lpthread

all: $(BUILD_DIR)/$(TARGET_EXEC)

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJS): FORCE
FORCE:

.PHONY: clean

clean:
	rm -r $(BUILD_DIR)

MKDIR_P ?= mkdir -p
