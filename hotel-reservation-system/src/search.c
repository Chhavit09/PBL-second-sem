#include <stdio.h>
#include <string.h>
#include "search.h"
#include "structures.h"

void searchByGuestName(const char *guestName) {
    FILE *file = fopen("data/reservations.txt", "r");
    if (!file) {
        printf("Error opening reservations file.\n");
        return;
    }

    Reservation reservation;
    char line[500];
    int found = 0;

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d,%99[^,],%99[^,],%19[^,],%d,%14[^,],%14[^,],%f,%d",
                   &reservation.reservationID, reservation.guestName, reservation.email, reservation.phone,
                   &reservation.roomNumber, reservation.checkInDate, reservation.checkOutDate,
                   &reservation.totalPrice, &reservation.status) == 9) {
            if (strcmp(reservation.guestName, guestName) == 0) {
                printf("Reservation ID: %d\nGuest Name: %s\nCheck-in Date: %s\nCheck-out Date: %s\nRoom Number: %d\n",
                       reservation.reservationID, reservation.guestName, reservation.checkInDate, reservation.checkOutDate, reservation.roomNumber);
                found = 1;
            }
        }
    }

    if (!found) {
        printf("No reservations found for guest: %s\n", guestName);
    }

    fclose(file);
}

void searchByRoomNumber(const char *roomNumber) {
    FILE *file = fopen("data/reservations.txt", "r");
    if (!file) {
        printf("Error opening reservations file.\n");
        return;
    }

    Reservation reservation;
    char line[500];
    int found = 0;
    int searchRoomNum = atoi(roomNumber);

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d,%99[^,],%99[^,],%19[^,],%d,%14[^,],%14[^,],%f,%d",
                   &reservation.reservationID, reservation.guestName, reservation.email, reservation.phone,
                   &reservation.roomNumber, reservation.checkInDate, reservation.checkOutDate,
                   &reservation.totalPrice, &reservation.status) == 9) {
            if (reservation.roomNumber == searchRoomNum) {
                printf("Reservation ID: %d\nGuest Name: %s\nCheck-in Date: %s\nCheck-out Date: %s\nRoom Number: %d\n",
                       reservation.reservationID, reservation.guestName, reservation.checkInDate, reservation.checkOutDate, reservation.roomNumber);
                found = 1;
            }
        }
    }

    if (!found) {
        printf("No reservations found for room number: %s\n", roomNumber);
    }

    fclose(file);
}