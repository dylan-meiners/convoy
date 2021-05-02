CC 			= gcc
BUILD_DIR 	?= ./build
SRC_DIR 	?= ./src

SRCS 		:= $(shell find $(SRC_DIR) -name *.c ! -name server.c ! -name client.c)
SERVER_SRC 	:= $(shell find $(SRC_DIR) -name server.c)
CLIENT_SRC 	:= $(shell find $(SRC_DIR) -name client.c)

OBJS 		:= $(SRCS:%=$(BUILD_DIR)/%.o)
SERVER_OBJ 	:= $(SERVER_SRC:%=$(BUILD_DIR)/%.o)
CLIENT_OBJ 	:= $(CLIENT_SRC:%=$(BUILD_DIR)/%.o)

TEST 		= NO_TEST
CPPFLAGS 	+= -D $(TEST)
LDFLAGS 	+= -lpthread

all: SERVER CLIENT

SERVER: $(SERVER_OBJ) $(OBJS)
	$(CC) $(OBJS) $< -o $(BUILD_DIR)/server $(LDFLAGS)

CLIENT: $(CLIENT_OBJ) $(OBJS)
	$(CC) $(OBJS) $< -o $(BUILD_DIR)/client $(LDFLAGS)

$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) -c $< -o $@

$(SERVER_OBJ): FORCE
$(CLIENT_OBJ): FORCE
$(OBJS): FORCE
FORCE:

.PHONY: clean

clean:
	rm -r $(BUILD_DIR)

MKDIR_P ?= mkdir -p
