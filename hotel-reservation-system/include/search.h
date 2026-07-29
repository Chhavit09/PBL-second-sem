#ifndef SEARCH_H
#define SEARCH_H

#include "structures.h"

// Function to search for a reservation by guest name
Reservation* searchReservationByName(const char* guestName, int* count);

// Function to search for a reservation by room number
Reservation* searchReservationByRoomNumber(int roomNumber, int* count);

#endif // SEARCH_H