CC = gcc
CFLAGS = -Iinclude -Wall -Wextra
SRC = src/main.c src/admin.c src/auth.c src/reservations.c src/search.c src/sort.c src/cancellation.c src/reports.c src/utils.c
OBJ = $(SRC:.c=.o)
EXEC = hotel_reservation_system

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all clean