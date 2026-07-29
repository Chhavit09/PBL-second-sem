#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <time.h>

#define MAX_GUEST_NAME 100
#define MAX_ROOM_TYPE 50
#define MAX_RESERVATIONS 1000

typedef struct {
    int id;
    char guestName[MAX_GUEST_NAME];
    char roomType[MAX_ROOM_TYPE];
    int roomNumber;
    time_t checkInDate;
    time_t checkOutDate;
    float totalAmount;
    int isActive; // 1 for active reservation, 0 for cancelled
} Reservation;

typedef struct {
    char username[50];
    char password[50];
} StaffCredentials;

typedef struct {
    int totalReservations;
    int occupiedRooms;
    float totalRevenue;
} Report;

#endif // STRUCTURES_H