CC = gcc
CFLAGS = -Wall -Wextra -std=c11

SRC = Test/test.c Helper/rbtHelper.c Utils/Insert.c Utils/display.c Utils/search.c

OBJ = $(SRC:.c=.o)

TARGET = RBT

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -IInclude -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)