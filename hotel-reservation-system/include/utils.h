#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

// Function prototypes
void clearInputBuffer();
int validateInput(int min, int max);
void pauseExecution();
void writeToFile(const char *filename, const char *data);
void readFromFile(const char *filename, char *buffer, size_t size);
void logError(const char *message);

#endif // UTILS_H