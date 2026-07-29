#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"


int fileExists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0;
}


void initializeDataFiles(void) {
    
    system("mkdir -p data");

    
    if (!fileExists("data/credentials.txt")) {
        FILE *file = fopen("data/credentials.txt", "w");
        if (file) {
            fprintf(file, "admin admin123\nmanager manager101\n");
            fclose(file);
            printf("✓ Credentials file created with default users.\n");
        }
    }

    
    if (!fileExists("data/reservations.txt")) {
        FILE *file = fopen("data/reservations.txt", "w");
        if (file) {
            fclose(file);
            printf("✓ Reservations file created.\n");
        }
    }

    
    if (!fileExists("data/rooms.txt")) {
        FILE *file = fopen("data/rooms.txt", "w");
        if (file) {
            fprintf(file, "101,Single,6225.00,0\n");
            fprintf(file, "102,Single,6225.00,0\n");
            fprintf(file, "103,Double,9960.00,0\n");
            fprintf(file, "104,Double,9960.00,0\n");
            fprintf(file, "105,Suite,16600.00,0\n");
            fprintf(file, "201,Single,6225.00,0\n");
            fprintf(file, "202,Single,6225.00,0\n");
            fprintf(file, "203,Double,9960.00,0\n");
            fprintf(file, "204,Double,9960.00,0\n");
            fprintf(file, "205,Suite,16600.00,0\n");
            fflush(file);
            fclose(file);
            printf("✓ Rooms file created with default rooms.\n");
        }
    }

    if (!fileExists("data/staff_credential.txt")) {
        FILE *file = fopen("data/staff_credential.txt", "w");
        if (file) {
            fflush(file);
            fclose(file);
            printf("✓ Staff file created.\n");
        }
    }
}


void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


int isValidDate(const char *date) {
    if (strlen(date) != 10) return 0;
    if (date[4] != '-' || date[7] != '-') return 0;
    
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (date[i] < '0' || date[i] > '9') return 0;
    }
    return 1;
}


int compareDates(const char *date1, const char *date2) {
    return strcmp(date1, date2);
}


void displayHeader(const char *title) {
    printf("%s\n", title);
}


void saveContinue(void) {
    printf("\nPress Enter to continue...");
    clearInputBuffer();
}