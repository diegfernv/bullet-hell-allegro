CC = gcc
CFLAGS = -I include $(shell pkg-config allegro-5 allegro_font-5 --cflags)
LDFLAGS = $(shell pkg-config allegro-5 allegro_font-5 allegro_primitives-5 --libs) -lm
SRC_DIR = src
SRC = main.c $(SRC_DIR)/bullet.c $(SRC_DIR)/game.c $(SRC_DIR)/enemy.c
OBJ = $(SRC:.c=.o)
TARGET = bullet_hell

# Targets and rules
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
