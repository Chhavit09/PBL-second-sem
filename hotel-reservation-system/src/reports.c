#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reports.h"
#include "reservations.h"

void generate_report() {
    FILE *fp;
    Reservation reservation;
    int total_reservations = 0;
    int confirmed_reservations = 0;
    float total_revenue = 0.0;
    char line[500];

    fp = fopen("data/reservations.txt", "r");
    if (fp == NULL) {
        printf("Error opening reservations file.\n");
        return;
    }

    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "%d,%99[^,],%99[^,],%19[^,],%d,%14[^,],%14[^,],%f,%d",
                   &reservation.reservationID, reservation.guestName, reservation.email, 
                   reservation.phone, &reservation.roomNumber, reservation.checkInDate, 
                   reservation.checkOutDate, &reservation.totalPrice, &reservation.status) == 9) {
            total_reservations++;
            if (reservation.status == 1) { 
                confirmed_reservations++;
                total_revenue += reservation.totalPrice;
            }
        }
    }

    fclose(fp);

    FILE *report_fp = fopen("data/reports.txt", "w");
    if (report_fp == NULL) {
        printf("Error opening reports file.\n");
        return;
    }

    fprintf(report_fp, "=== HOTEL MANAGEMENT REPORT ===\n\n");
    fprintf(report_fp, "Total Reservations: %d\n", total_reservations);
    fprintf(report_fp, "Confirmed Reservations: %d\n", confirmed_reservations);
    fprintf(report_fp, "Total Revenue: ₹%.2f\n", total_revenue);
    if (confirmed_reservations > 0) {
        fprintf(report_fp, "Average Per Reservation: ₹%.2f\n", total_revenue / confirmed_reservations);
    }

    fflush(report_fp);
    fclose(report_fp);
    printf("✓ Report generated successfully.\n");
}