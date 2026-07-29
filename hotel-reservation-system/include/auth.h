#ifndef AUTH_H
#define AUTH_H

#include <stdbool.h>

// Function to authenticate staff login
bool authenticate(const char *username, const char *password);

// Function to load staff credentials from file
void load_credentials(const char *filename);

// Function to verify staff credentials
bool verify_credentials(const char *username, const char *password);

#endif // AUTH_H