CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

SRC = src/main.c \
      src/avl/avl_tree.c \
      src/parsing/csv_parser.c \
      src/histo/histogram.c \
      src/network/network.c \
      src/network/network_builder.c \
      src/network/losses.c

OBJ = $(SRC:.c=.o)
TARGET = wildwater_test

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJ) $(TARGET)
