CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude

SRC_DIR = src
INCLUDE_DIR = include
BIN_DIR = bin

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(SRCS))
DEPS = $(wildcard $(INCLUDE_DIR)/*.h)

all: createArchive extractArchive

createArchive: $(BIN_DIR)/createArchive.o
	$(CC) $(CFLAGS) -o $@ $<

extractArchive: $(BIN_DIR)/extractArchive.o
	$(CC) $(CFLAGS) -o $@ $<

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(BIN_DIR)/*.o createArchive extractArchive

