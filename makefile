CC = gcc
CFLAGS = -Wall -Wextra -g -std=c11 -Iinclude -Ofast
LIBS = -lraylib -lm -ldl -lpthread -lrt -lX11

# -- Structure --
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

$(shell mkdir -p $(OBJ_DIR) $(BIN_DIR))

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
EXECUTABLE = $(BIN_DIR)/sim

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	@$(CC) $^ -o $@ $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR) $(BIN_DIR)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

.PHONY: all clean run