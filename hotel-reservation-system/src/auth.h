#ifndef AUTH_H
#define AUTH_H

#include "structures.h"

// Function declarations for authentication module
int authenticateUser(void);
int validateCredentials(const char *username, const char *password);
void registerNewUser(void);
void displayLoginMenu(void);
void viewAllStaff(void);
void addStaff(void);
void deleteStaff(void);
void updateStaffPassword(void);

#endif
