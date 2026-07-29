#ifndef ADMIN_H
#define ADMIN_H

#include "structures.h"

// Function to add a new reservation
void addReservation(Reservation reservation);

// Function to modify an existing reservation
void modifyReservation(int reservationID, Reservation updatedReservation);

// Function to delete a reservation
void deleteReservation(int reservationID);

// Function to list all reservations
void listReservations();

// Function to search for a reservation by guest name
void searchReservationByName(const char* guestName);

// Function to search for a reservation by room number
void searchReservationByRoomNumber(int roomNumber);

// Function to cancel a reservation
void cancelReservation(int reservationID);

// Function to generate reports on reservations
void generateReports();

#endif // ADMIN_H