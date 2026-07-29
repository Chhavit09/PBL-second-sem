#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "admin.h"
#include "auth.h"
#include "utils.h"


void displayAdminMenu(void) {
    printf("\n");
    displayHeader("=== ADMIN MENU ===");
    printf("1. View All Reservations\n");
    printf("2. View Available Rooms\n");
    printf("3. Manage Rooms\n");
    printf("4. Manage Staff Credentials\n");
    printf("5. Generate Occupancy Report\n");
    printf("6. Generate Revenue Report\n");
    printf("7. Return to Main Menu\n");
    printf("Select option: ");
}

void viewAllReservations(void) {
    printf("\n");
    displayHeader("=== ALL RESERVATIONS (ADMIN VIEW) ===");
    
    FILE *file = fopen("data/reservations.txt", "r");
    if (file == NULL) {
        printf("No reservations found.\n");
        return;
    }

    Reservation res;
    char line[500];
    int count = 0;
    
    printf("%-8s | %-20s | %-6s | %-12s | %-12s | %-10s\n",
           "ID", "Guest", "Room", "Check-in", "Check-out", "Price");
    printf("------------------------------------------------------------------\n");

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d,%99[^,],%99[^,],%19[^,],%d,%14[^,],%14[^,],%f,%d",
                   &res.reservationID, res.guestName, res.email, res.phone,
                   &res.roomNumber, res.checkInDate, res.checkOutDate,
                   &res.totalPrice, &res.status) == 9) {
            
            printf("%-8d | %-20s | %-6d | %-12s | %-12s | ₹%-9.2f\n",
                   res.reservationID, res.guestName, res.roomNumber,
                   res.checkInDate, res.checkOutDate, res.totalPrice);
            count++;
        }
    }
    
    fclose(file);
    printf("\nTotal: %d reservations\n", count);
}

void viewAvailableRooms(void) {
    printf("\n");
    displayHeader("=== AVAILABLE ROOMS ===");
    
    FILE *file = fopen("data/rooms.txt", "r");
    if (file == NULL) {
        printf("No rooms in database.\n");
        return;
    }

    Room room;
    char line[200];
    int count = 0;
    
    printf("%-6s | %-12s | %-8s | %-10s\n", "Room", "Type", "Price", "Status");
    printf("----------------------------------------\n");

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d,%29[^,],%f,%d",
                   &room.roomNumber, room.roomType, &room.price, &room.isOccupied) == 4) {
            
            printf("%-6d | %-12s | ₹%-7.2f | %s\n",
                   room.roomNumber, room.roomType, room.price,
                   room.isOccupied ? "Occupied" : "Available");
            if (!room.isOccupied) count++;
        }
    }
    
    fclose(file);
    printf("\nAvailable Rooms: %d\n", count);
}

void addRoom(void) {
    printf("\n=== ADD NEW ROOM ===\n");
    
    Room newRoom;
    printf("\nRoom Number: ");
    scanf("%d", &newRoom.roomNumber);
    printf("Room Type (Single/Double/Suite): ");
    scanf("%29s", newRoom.roomType);
    printf("Price per night: ");
    scanf("%f", &newRoom.price);
    newRoom.isOccupied = 0;

    FILE *file = fopen("data/rooms.txt", "a");
    if (file == NULL) {
        printf("Error opening rooms file.\n");
        return;
    }

    fprintf(file, "%d,%s,%.2f,%d\n", newRoom.roomNumber, newRoom.roomType, newRoom.price, newRoom.isOccupied);
    fclose(file);
    printf("✓ Room #%d added successfully!\n", newRoom.roomNumber);
}

void viewRooms(void) {
    printf("\n");
    displayHeader("=== ALL ROOMS ===");
    
    FILE *file = fopen("data/rooms.txt", "r");
    if (file == NULL) {
        printf("No rooms in database.\n");
        return;
    }

    Room room;
    char line[200];
    int count = 0;
    
    printf("%-6s | %-12s | %-8s | %-10s\n", "Room", "Type", "Price", "Status");
    printf("----------------------------------------\n");

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d,%29[^,],%f,%d",
                   &room.roomNumber, room.roomType, &room.price, &room.isOccupied) == 4) {
            
            printf("%-6d | %-12s | ₹%-7.2f | %s\n",
                   room.roomNumber, room.roomType, room.price,
                   room.isOccupied ? "Occupied" : "Available");
            count++;
        }
    }
    
    fclose(file);
    printf("\nTotal Rooms: %d\n", count);
}

void updateRoomStatus(void) {
    printf("\n=== UPDATE ROOM STATUS ===\n");
    
    int roomNumber, newStatus;
    printf("Enter Room Number: ");
    scanf("%d", &roomNumber);
    printf("Enter New Status (1 for Occupied, 0 for Available): ");
    scanf("%d", &newStatus);
    
    if (newStatus != 0 && newStatus != 1) {
        printf("✗ Invalid status. Please use 1 (Occupied) or 0 (Available).\n");
        return;
    }

    FILE *file = fopen("data/rooms.txt", "r");
    FILE *temp = fopen("data/rooms_temp.txt", "w");
    
    if (file == NULL || temp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    Room room;
    char line[200];
    int found = 0;
    
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d,%29[^,],%f,%d",
                   &room.roomNumber, room.roomType, &room.price, &room.isOccupied) == 4) {
            
            if (room.roomNumber == roomNumber) {
                room.isOccupied = newStatus;
                found = 1;
            }
            
            fprintf(temp, "%d,%s,%.2f,%d\n",
                    room.roomNumber, room.roomType, room.price, room.isOccupied);
        }
    }
    
    fclose(file);
    fclose(temp);
    
    if (found) {
        remove("data/rooms.txt");
        rename("data/rooms_temp.txt", "data/rooms.txt");
        printf("✓ Room #%d status updated to %s!\n", roomNumber, newStatus ? "Occupied" : "Available");
    } else {
        remove("data/rooms_temp.txt");
        printf("✗ Room #%d not found.\n", roomNumber);
    }
}

void manageRooms(void) {
    int choice;
    
    while (1) {
        printf("\n");
        displayHeader("=== ROOM MANAGEMENT ===");
        printf("1. Add Room\n");
        printf("2. View All Rooms\n");
        printf("3. Update Room Status\n");
        printf("4. Return to Admin Menu\n");
        printf("Select option: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                addRoom();
                break;
            case 2:
                viewRooms();
                break;
            case 3:
                updateRoomStatus();
                break;
            case 4:
                return;
            default:
                printf("✗ Invalid option.\n");
        }
    }
}

void manageStaff(void) {
    int choice;
    
    while (1) {
        printf("\n");
        displayHeader("=== STAFF MANAGEMENT ===");
        printf("1. View All Staff\n");
        printf("2. Add New Staff\n");
        printf("3. Delete Staff\n");
        printf("4. Update Staff Password\n");
        printf("5. Return to Admin Menu\n");
        printf("Select option: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                viewAllStaff();
                break;
            case 2:
                addStaff();
                break;
            case 3:
                deleteStaff();
                break;
            case 4:
                updateStaffPassword();
                break;
            case 5:
                return;
            default:
                printf("✗ Invalid option.\n");
        }
        saveContinue();
    }
}

void generateOccupancyReport(void) {
    printf("\n");
    displayHeader("=== OCCUPANCY REPORT ===");
    
    FILE *resFile = fopen("data/reservations.txt", "r");
    FILE *roomFile = fopen("data/rooms.txt", "r");
    
    if (resFile == NULL || roomFile == NULL) {
        printf("Error opening files.\n");
        return;
    }

    Reservation res;
    char line[500];
    int totalRooms = 0, occupiedRooms = 0;

    while (fgets(line, sizeof(line), roomFile)) {
        totalRooms++;
    }

    while (fgets(line, sizeof(line), resFile)) {
        if (sscanf(line, "%d,%99[^,],%99[^,],%19[^,],%d,%14[^,],%14[^,],%f,%d",
                   &res.reservationID, res.guestName, res.email, res.phone,
                   &res.roomNumber, res.checkInDate, res.checkOutDate,
                   &res.totalPrice, &res.status) == 9) {
            if (res.status != 2) occupiedRooms++;
        }
    }

    int available = totalRooms - occupiedRooms;
    float occupancyRate = (totalRooms > 0) ? ((float)occupiedRooms / totalRooms) * 100 : 0;

    printf("\nTotal Rooms: %d\n", totalRooms);
    printf("Occupied Rooms: %d\n", occupiedRooms);
    printf("Available Rooms: %d\n", available);
    printf("Occupancy Rate: %.2f%%\n", occupancyRate);

    fclose(resFile);
    fclose(roomFile);
}

void generateRevenueReport(void) {
    printf("\n");
    displayHeader("=== REVENUE REPORT ===");
    
    FILE *file = fopen("data/reservations.txt", "r");
    if (file == NULL) {
        printf("No reservations found.\n");
        return;
    }

    Reservation res;
    char line[500];
    float totalRevenue = 0.0;
    int confirmedCount = 0;

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d,%99[^,],%99[^,],%19[^,],%d,%14[^,],%14[^,],%f,%d",
                   &res.reservationID, res.guestName, res.email, res.phone,
                   &res.roomNumber, res.checkInDate, res.checkOutDate,
                   &res.totalPrice, &res.status) == 9) {
            if (res.status == 1) {
                totalRevenue += res.totalPrice;
                confirmedCount++;
            }
        }
    }

    printf("\nTotal Confirmed Reservations: %d\n", confirmedCount);
    printf("Total Revenue: ₹%.2f\n", totalRevenue);
    if (confirmedCount > 0)
        printf("Average Per Reservation: ₹%.2f\n", totalRevenue / confirmedCount);

    fclose(file);
}

void generateReports(void) {
    int choice;
    
    while (1) {
        printf("\n");
        displayHeader("=== REPORTS ===");
        printf("1. View All Reservations\n");
        printf("2. View Available Rooms\n");
        printf("3. Occupancy Report\n");
        printf("4. Revenue Report\n");
        printf("5. Return to Main Menu\n");
        printf("Select option: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                viewAllReservations();
                break;
            case 2:
                viewAvailableRooms();
                break;
            case 3:
                generateOccupancyReport();
                break;
            case 4:
                generateRevenueReport();
                break;
            case 5:
                return;
            default:
                printf("✗ Invalid option.\n");
        }
        saveContinue();
    }
}

int handleAdminMenu(void) {
    int choice;
    
    while (1) {
        displayAdminMenu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                viewAllReservations();
                break;
            case 2:
                viewAvailableRooms();
                break;
            case 3:
                manageRooms();
                break;
            case 4:
                manageStaff();
                break;
            case 5:
                generateOccupancyReport();
                break;
            case 6:
                generateRevenueReport();
                break;
            case 7:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
        saveContinue();
    }
    return 0;
}
