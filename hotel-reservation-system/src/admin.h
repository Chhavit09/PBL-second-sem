#ifndef ADMIN_H
#define ADMIN_H

#include "structures.h"

// Function declarations for admin module
void generateReports(void);
void displayAdminMenu(void);
int handleAdminMenu(void);
void viewAllReservations(void);
void viewAvailableRooms(void);
void generateOccupancyReport(void);
void generateRevenueReport(void);
void manageRooms(void);
void manageStaff(void);
void addRoom(void);
void viewRooms(void);
void updateRoomStatus(void);

#endif
