#ifndef UTILS_H
#define UTILS_H

#include "structures.h"

void initializeDataFiles(void);
int fileExists(const char *filename);
void clearInputBuffer(void);
int isValidDate(const char *date);
int compareDates(const char *date1, const char *date2);
void displayHeader(const char *title);
void saveContinue(void);

#endif
