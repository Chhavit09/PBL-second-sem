#ifndef REPORTS_H
#define REPORTS_H

#include "structures.h"

// Function to generate a report of room occupancy
void generateOccupancyReport();

// Function to generate a report of total reservations
void generateTotalReservationsReport();

// Function to generate a revenue report
void generateRevenueReport();

// Function to save report data to a file
void saveReportToFile(const char *filename, const char *reportData);

#endif // REPORTS_H