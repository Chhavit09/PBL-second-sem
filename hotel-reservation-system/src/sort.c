#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "sort.h"

void sortByCheckInDate(Reservation *reservations, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (reservations[j].checkInDate > reservations[j + 1].checkInDate) {
                Reservation temp = reservations[j];
                reservations[j] = reservations[j + 1];
                reservations[j + 1] = temp;
            }
        }
    }
}

void sortByRoomType(Reservation *reservations, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcasecmp(reservations[j].roomType, reservations[j + 1].roomType) > 0) {
                Reservation temp = reservations[j];
                reservations[j] = reservations[j + 1];
                reservations[j + 1] = temp;
            }
        }
    }
}