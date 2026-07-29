#include <stdio.h>
#include <stdlib.h>
#include "auth.h"
#include "admin.h"
#include "reservations.h"
#include "utils.h"

void displayMainMenu(void) {
    printf("\n");
    displayHeader("=== HOTEL MANAGEMENT SYSTEM ===");
    printf("1. Manage Reservations\n");
    printf("2. Generate Reports\n");
    printf("3. Admin Panel\n");
    printf("4. Exit\n");
    printf("Select an option: ");
}

int main(void) {
    int choice;
    
    
    initializeDataFiles();
    printf("\n");
    

    authenticateUser();

    do {
        displayMainMenu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                manageReservations();
                break;
            case 2:
                generateReports();
                break;
            case 3:
                handleAdminMenu();
                break;
            case 4:
                printf("\nThank you for using Hotel Management System. Goodbye!\n\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}
