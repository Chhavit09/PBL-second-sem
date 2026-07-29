#ifndef RESERVATIONS_H
#define RESERVATIONS_H

#include "structures.h"

// Function to add a new reservation
void addReservation(Reservation reservation);

// Function to modify an existing reservation
void modifyReservation(int reservationID, Reservation updatedReservation);

// Function to delete a reservation
void deleteReservation(int reservationID);

// Function to load reservations from file
void loadReservations();

// Function to save reservations to file
void saveReservations();

// Function to get reservation details by ID
Reservation getReservationByID(int reservationID);

// Function to list all reservations
void listReservations();

// Function to search reservations by guest name
void searchReservationsByName(const char* guestName);

// Function to search reservations by room number
void searchReservationsByRoomNumber(int roomNumber);

#endif // RESERVATIONS_H