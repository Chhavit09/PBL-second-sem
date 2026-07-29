#ifndef SORT_H
#define SORT_H

#include "structures.h"

// Function to sort reservations by check-in date
void sortByCheckInDate(Reservation *reservations, int count);

// Function to sort reservations by room type
void sortByRoomType(Reservation *reservations, int count);

#endif // SORT_H