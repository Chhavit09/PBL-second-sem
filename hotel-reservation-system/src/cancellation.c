#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cancellation.h"
#include "structures.h"

void cancelReservation(int reservationID) {
    FILE *file, *tempFile;
    struct Reservation reservation;
    int found = 0;

    file = fopen("data/reservations.txt", "r");
    tempFile = fopen("data/temp_reservations.txt", "w");

    if (file == NULL || tempFile == NULL) {
        printf("Error opening file.\n");
        return;
    }

    while (fread(&reservation, sizeof(struct Reservation), 1, file)) {
        if (reservation.reservationID == reservationID) {
            found = 1;
            printf("Reservation ID %d has been cancelled.\n", reservationID);
        } else {
            fwrite(&reservation, sizeof(struct Reservation), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove("data/reservations.txt");
        rename("data/temp_reservations.txt", "data/reservations.txt");
    } else {
        printf("Reservation ID %d not found.\n", reservationID);
        remove("data/temp_reservations.txt");
    }
}