#ifndef RESERVATIONS_H
#define RESERVATIONS_H

#include "structures.h"

int manageReservations(void);
void addReservation(void);
void viewReservations(void);
void cancelReservation(void);
void deleteReservation(void);
void searchReservation(void);
void updateReservationStatus(void);
int generateReservationID(void);
int getHighestReservationID(void);
int calculateDays(const char *checkIn, const char *checkOut);
float getRoomPriceByType(const char *roomType);
void displayAvailableRoomNumbers(const char *roomType);
void updateRoomOccupancy(int roomNumber, int isOccupied);
int checkRoomAvailability(int roomNumber, const char *checkIn, const char *checkOut);
void displayReservationMenu(void);

#endif
