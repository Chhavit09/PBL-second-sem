#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "reservations.h"
#include "utils.h"

int reservationCounter = 1000;


int getHighestReservationID(void) {
    FILE *file = fopen("data/reservations.txt", "r");
    if (file == NULL) {
        return 1000;
    }

    int highestID = 1000;
    int id;
    char line[500];
    
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d,", &id) == 1) {
            if (id > highestID) {
                highestID = id;
            }
        }
    }
    
    fclose(file);
    return highestID;
}


int generateReservationID(void) {
    return ++reservationCounter;
}


int calculateDays(const char *checkIn, const char *checkOut) {
    int inYear, inMonth, inDay;
    int outYear, outMonth, outDay;
    
    sscanf(checkIn, "%d-%d-%d", &inYear, &inMonth, &inDay);
    sscanf(checkOut, "%d-%d-%d", &outYear, &outMonth, &outDay);
    
    int inDate = inYear * 10000 + inMonth * 100 + inDay;
    int outDate = outYear * 10000 + outMonth * 100 + outDay;
    
    return (outDate - inDate);
}


float getRoomPriceByType(const char *roomType) {
    FILE *file = fopen("data/rooms.txt", "r");
    if (file == NULL) {
        return 0.0;
    }

    Room room;
    char line[200];
    
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d,%29[^,],%f,%d",
                   &room.roomNumber, room.roomType, &room.price, &room.isOccupied) == 4) {
            if (strcasecmp(room.roomType, roomType) == 0) {
                fclose(file);
                return room.price;
            }
        }
    }
    
    fclose(file);
    return 0.0;
}


void displayAvailableRoomNumbers(const char *roomType) {
    FILE *file = fopen("data/rooms.txt", "r");
    if (file == NULL) {
        printf("Error opening rooms file.\n");
        return;
    }

    Room room;
    char line[200];
    int availableCount = 0;
    
    printf("\nAvailable %s Room Numbers: ", roomType);
    
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d,%29[^,],%f,%d",
                   &room.roomNumber, room.roomType, &room.price, &room.isOccupied) == 4) {
            if (strcasecmp(room.roomType, roomType) == 0 && !room.isOccupied) {
                if (availableCount > 0) printf(", ");
                printf("#%d", room.roomNumber);
                availableCount++;
            }
        }
    }
    
    if (availableCount == 0) {
        printf("None");
    }
    printf("\n");
    
    fclose(file);
}


void updateRoomOccupancy(int roomNumber, int isOccupied) {
    FILE *file = fopen("data/rooms.txt", "r");
    FILE *temp = fopen("data/rooms_temp.txt", "w");
    
    if (file == NULL || temp == NULL) {
        printf("Error updating room occupancy.\n");
        return;
    }

    Room room;
    char line[200];
    
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d,%29[^,],%f,%d",
                   &room.roomNumber, room.roomType, &room.price, &room.isOccupied) == 4) {
            
            if (room.roomNumber == roomNumber) {
                room.isOccupied = isOccupied;
            }
            
            fprintf(temp, "%d,%s,%.2f,%d\n",
                    room.roomNumber, room.roomType, room.price, room.isOccupied);
        }
    }
    
    fclose(file);
    fclose(temp);
    
    remove("data/rooms.txt");
    rename("data/rooms_temp.txt", "data/rooms.txt");
}


int checkRoomAvailability(int roomNumber, const char *checkIn, const char *checkOut) {
    FILE *file = fopen("data/reservations.txt", "r");
    if (file == NULL) {
        return 1; 
    }

    Reservation res;
    char line[500];
    
    while (fgets(line, sizeof(line), file)) {
        
        if (sscanf(line, "%d,%99[^,],%99[^,],%19[^,],%d,%14[^,],%14[^,],%f,%d",
                   &res.reservationID, res.guestName, res.email, res.phone,
                   &res.roomNumber, res.checkInDate, res.checkOutDate,
                   &res.totalPrice, &res.status) == 9) {
            
            if (res.roomNumber == roomNumber && res.status != 2) { 
                
                if ((strcmp(checkIn, res.checkOutDate) < 0) && (strcmp(checkOut, res.checkInDate) > 0)) {
                    fclose(file);
                    return 0; 
                }
            }
        }
    }
    
    fclose(file);
    return 1; 
}


void displayReservationMenu(void) {
    printf("\n");
    displayHeader("=== RESERVATION MANAGEMENT ===");
    printf("1. Add New Reservation\n");
    printf("2. View All Reservations\n");
    printf("3. Search Reservation\n");
    printf("4. Update Reservation Status\n");
    printf("5. Cancel Reservation\n");
    printf("6. Delete Reservation\n");
    printf("7. Return to Main Menu\n");
    printf("Select option: ");
}


void addReservation(void) {
    printf("\n=== ADD NEW RESERVATION ===");
    
    Reservation newRes;
    newRes.reservationID = generateReservationID();
    newRes.status = 0;

    clearInputBuffer();
    
    printf("\nGuest Name: ");
    fgets(newRes.guestName, sizeof(newRes.guestName), stdin);
    newRes.guestName[strcspn(newRes.guestName, "\n")] = 0;
    
    printf("Email: ");
    scanf("%99s", newRes.email);
    printf("Phone: ");
    scanf("%19s", newRes.phone);
    
    char roomType[30];
    printf("Room Type (Single/Double/Suite): ");
    scanf("%29s", roomType);
    
    printf("Check-in Date (YYYY-MM-DD): ");
    scanf("%14s", newRes.checkInDate);
    
    if (!isValidDate(newRes.checkInDate)) {
        printf("✗ Invalid check-in date format. Please use YYYY-MM-DD.\n");
        return;
    }
    
    printf("Check-out Date (YYYY-MM-DD): ");
    scanf("%14s", newRes.checkOutDate);
    
    if (!isValidDate(newRes.checkOutDate)) {
        printf("✗ Invalid check-out date format. Please use YYYY-MM-DD.\n");
        return;
    }
    
    
    if (strcmp(newRes.checkInDate, newRes.checkOutDate) >= 0) {
        printf("✗ Invalid dates. Check-out date must be after check-in date.\n");
        return;
    }
    
    
    int days = calculateDays(newRes.checkInDate, newRes.checkOutDate);
    if (days <= 0) {
        printf("✗ Invalid dates. Check-out date must be after check-in date.\n");
        return;
    }
    
    
    float pricePerDay = getRoomPriceByType(roomType);
    if (pricePerDay <= 0) {
        printf("✗ Invalid room type. Please use Single, Double, or Suite.\n");
        return;
    }
    
    
    newRes.totalPrice = pricePerDay * days;
    
    
    printf("\n=== BOOKING SUMMARY ===\n");
    printf("Room Type: %s\n", roomType);
    printf("Check-in: %s\n", newRes.checkInDate);
    printf("Check-out: %s\n", newRes.checkOutDate);
    printf("Number of Days: %d\n", days);
    printf("Price per Night: ₹%.2f\n", pricePerDay);
    printf("Total Price: ₹%.2f\n\n", newRes.totalPrice);
    
    
    FILE *roomFile = fopen("data/rooms.txt", "r");
    if (roomFile == NULL) {
        printf("Error opening rooms file.\n");
        return;
    }

    Room room;
    char line[200];
    int roomFound = 0;
    
    while (fgets(line, sizeof(line), roomFile)) {
        if (sscanf(line, "%d,%29[^,],%f,%d",
                   &room.roomNumber, room.roomType, &room.price, &room.isOccupied) == 4) {
            if (strcasecmp(room.roomType, roomType) == 0 && !room.isOccupied) {
                
                if (checkRoomAvailability(room.roomNumber, newRes.checkInDate, newRes.checkOutDate)) {
                    newRes.roomNumber = room.roomNumber;
                    roomFound = 1;
                    break;
                }
            }
        }
    }
    fclose(roomFile);
    
    if (!roomFound) {
        printf("✗ No %s rooms available for the selected dates.\n", roomType);
        return;
    }
    
    printf("Assigned Room: #%d\n", newRes.roomNumber);
    
    
    displayAvailableRoomNumbers(roomType);
    
    
    printf("\n=== RESERVATION STATUS ===\n");
    printf("1. Pending (0)\n");
    printf("2. Confirmed (1)\n");
    printf("3. Cancelled (2)\n");
    printf("Select status: ");
    scanf("%d", &newRes.status);
    
    if (newRes.status < 0 || newRes.status > 2) {
        printf("✗ Invalid status. Setting to Pending.\n");
        newRes.status = 0;
    }
    
    FILE *file = fopen("data/reservations.txt", "a");
    if (file == NULL) {
        printf("Error opening reservations file.\n");
        return;
    }

    fprintf(file, "%d,%s,%s,%s,%d,%s,%s,%.2f,%d\n",
            newRes.reservationID, newRes.guestName, newRes.email, newRes.phone,
            newRes.roomNumber, newRes.checkInDate, newRes.checkOutDate,
            newRes.totalPrice, newRes.status);
    
    fflush(file);
    fclose(file);
    
  
    if (newRes.status == 1) {
        updateRoomOccupancy(newRes.roomNumber, 1);
        printf("✓ Room #%d marked as occupied.\n", newRes.roomNumber);
    } else if (newRes.status == 2) {
        printf("ℹ Reservation marked as cancelled.\n");
    }
    printf("✓ Reservation #%d added successfully!\n", newRes.reservationID);
}


void viewReservations(void) {
    printf("\n");
    displayHeader("=== ALL RESERVATIONS ===");
    
    FILE *file = fopen("data/reservations.txt", "r");
    if (file == NULL) {
        printf("No reservations found.\n");
        return;
    }

    Reservation res;
    char line[500];
    int count = 0;
    
    printf("%-8s | %-20s | %-15s | %-6s | %-12s | %-12s | %-10s | %-10s\n",
           "ID", "Guest Name", "Email", "Room", "Check-in", "Check-out", "Price", "Status");
    printf("---------------------------------------------------------------------------------------------------------\n");

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d,%99[^,],%99[^,],%19[^,],%d,%14[^,],%14[^,],%f,%d",
                   &res.reservationID, res.guestName, res.email, res.phone,
                   &res.roomNumber, res.checkInDate, res.checkOutDate,
                   &res.totalPrice, &res.status) == 9) {
            
            const char *status = (res.status == 0) ? "Pending" : (res.status == 1) ? "Confirmed" : "Cancelled";
            printf("%-8d | %-20s | %-15s | %-6d | %-12s | %-12s | ₹%-9.2f | %s\n",
                   res.reservationID, res.guestName, res.email, res.roomNumber,
                   res.checkInDate, res.checkOutDate, res.totalPrice, status);
            count++;
        }
    }
    
    fclose(file);
    printf("\nTotal Reservations: %d\n", count);
}


void searchReservation(void) {
    printf("\n=== SEARCH RESERVATION ===");
    int searchID;
    printf("\nEnter Reservation ID: ");
    scanf("%d", &searchID);

    FILE *file = fopen("data/reservations.txt", "r");
    if (file == NULL) {
        printf("No reservations found.\n");
        return;
    }

    Reservation res;
    char line[500];
    int found = 0;
    
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d,%99[^,],%99[^,],%19[^,],%d,%14[^,],%14[^,],%f,%d",
                   &res.reservationID, res.guestName, res.email, res.phone,
                   &res.roomNumber, res.checkInDate, res.checkOutDate,
                   &res.totalPrice, &res.status) == 9) {
            
            if (res.reservationID == searchID) {
                found = 1;
                printf("\n✓ Reservation Found:\n");
                printf("ID: %d\n", res.reservationID);
                printf("Guest Name: %s\n", res.guestName);
                printf("Email: %s\n", res.email);
                printf("Phone: %s\n", res.phone);
                printf("Room Number: %d\n", res.roomNumber);
                printf("Check-in: %s\n", res.checkInDate);
                printf("Check-out: %s\n", res.checkOutDate);
                printf("Total Price: ₹%.2f\n", res.totalPrice);
                printf("Status: %s\n", (res.status == 0) ? "Pending" : (res.status == 1) ? "Confirmed" : "Cancelled");
                break;
            }
        }
    }
    
    if (!found) {
        printf("✗ Reservation ID %d not found.\n", searchID);
    }
    
    fclose(file);
}


void updateReservationStatus(void) {
    printf("\n=== UPDATE RESERVATION STATUS ===");
    int updateID;
    printf("\nEnter Reservation ID to update: ");
    scanf("%d", &updateID);

    FILE *file = fopen("data/reservations.txt", "r");
    FILE *temp = fopen("data/reservations_temp.txt", "w");
    
    if (file == NULL || temp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    Reservation res;
    char line[500];
    int found = 0;
    int oldStatus = -1;
    
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d,%99[^,],%99[^,],%19[^,],%d,%14[^,],%14[^,],%f,%d",
                   &res.reservationID, res.guestName, res.email, res.phone,
                   &res.roomNumber, res.checkInDate, res.checkOutDate,
                   &res.totalPrice, &res.status) == 9) {
            
            if (res.reservationID == updateID) {
                found = 1;
                oldStatus = res.status;
                
                
                printf("\n✓ Reservation Found!\n");
                printf("Guest Name: %s\n", res.guestName);
                printf("Current Status: %s\n", 
                    (res.status == 0) ? "Pending" : (res.status == 1) ? "Confirmed" : "Cancelled");
                printf("Room Number: %d\n\n", res.roomNumber);
                
                
                printf("=== SELECT NEW STATUS ===");
                printf("\n1. Pending (0)\n");
                printf("2. Confirmed (1)\n");
                printf("3. Cancelled (2)\n");
                printf("Select new status: ");
                int newStatus;
                scanf("%d", &newStatus);
                
                if (newStatus < 0 || newStatus > 2) {
                    printf("✗ Invalid status. No changes made.\n");
                    fclose(file);
                    fclose(temp);
                    remove("data/reservations_temp.txt");
                    return;
                }
                
                res.status = newStatus;
            }
            
            fprintf(temp, "%d,%s,%s,%s,%d,%s,%s,%.2f,%d\n",
                    res.reservationID, res.guestName, res.email, res.phone,
                    res.roomNumber, res.checkInDate, res.checkOutDate,
                    res.totalPrice, res.status);
        }
    }
    
    fclose(file);
    fclose(temp);
    
    if (found) {
        remove("data/reservations.txt");
        rename("data/reservations_temp.txt", "data/reservations.txt");
        
       
        if (oldStatus != res.status) {
            if (res.status == 1) {
                
                updateRoomOccupancy(res.roomNumber, 1);
                printf("✓ Room #%d marked as occupied.\n", res.roomNumber);
            } else if (oldStatus == 1) {
                
                updateRoomOccupancy(res.roomNumber, 0);
                printf("✓ Room #%d marked as available.\n", res.roomNumber);
            }
        }
        
        printf("✓ Reservation #%d status updated successfully!\n", updateID);
    } else {
        remove("data/reservations_temp.txt");
        printf("✗ Reservation ID %d not found.\n", updateID);
    }
}


void cancelReservation(void) {
    printf("\n=== CANCEL RESERVATION ===");
    int cancelID;
    printf("\nEnter Reservation ID to cancel: ");
    scanf("%d", &cancelID);

    FILE *file = fopen("data/reservations.txt", "r");
    FILE *temp = fopen("data/reservations_temp.txt", "w");
    
    if (file == NULL || temp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    Reservation res;
    char line[500];
    int found = 0;
    int wasConfirmed = 0;
    
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d,%99[^,],%99[^,],%19[^,],%d,%14[^,],%14[^,],%f,%d",
                   &res.reservationID, res.guestName, res.email, res.phone,
                   &res.roomNumber, res.checkInDate, res.checkOutDate,
                   &res.totalPrice, &res.status) == 9) {
            
            if (res.reservationID == cancelID) {
                if (res.status == 1) {
                    wasConfirmed = 1;
                }
                res.status = 2; 
                found = 1;
            }
            
            fprintf(temp, "%d,%s,%s,%s,%d,%s,%s,%.2f,%d\n",
                    res.reservationID, res.guestName, res.email, res.phone,
                    res.roomNumber, res.checkInDate, res.checkOutDate,
                    res.totalPrice, res.status);
        }
    }
    
    fclose(file);
    fclose(temp);
    
    if (found) {
        remove("data/reservations.txt");
        rename("data/reservations_temp.txt", "data/reservations.txt");
        
        
        if (wasConfirmed) {
            updateRoomOccupancy(res.roomNumber, 0);
            printf("✓ Room #%d marked as available.\n", res.roomNumber);
        }
        
        printf("✓ Reservation #%d cancelled successfully!\n", cancelID);
    } else {
        remove("data/reservations_temp.txt");
        printf("✗ Reservation ID %d not found.\n", cancelID);
    }
}


void deleteReservation(void) {
    printf("\n=== DELETE RESERVATION ===");
    int deleteID;
    printf("\nEnter Reservation ID to delete: ");
    scanf("%d", &deleteID);
    
    
    printf("\n⚠ WARNING: This will permanently delete the reservation!\n");
    printf("Enter reservation ID again to confirm deletion: ");
    int confirmID;
    scanf("%d", &confirmID);
    
    if (deleteID != confirmID) {
        printf("✗ Confirmation failed. Deletion cancelled.\n");
        return;
    }

    FILE *file = fopen("data/reservations.txt", "r");
    FILE *temp = fopen("data/reservations_temp.txt", "w");
    
    if (file == NULL || temp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    Reservation res;
    char line[500];
    int found = 0;
    int wasConfirmed = 0;
    int roomNumber = 0;
    
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d,%99[^,],%99[^,],%19[^,],%d,%14[^,],%14[^,],%f,%d",
                   &res.reservationID, res.guestName, res.email, res.phone,
                   &res.roomNumber, res.checkInDate, res.checkOutDate,
                   &res.totalPrice, &res.status) == 9) {
            
            if (res.reservationID == deleteID) {
                if (res.status == 1) {
                    wasConfirmed = 1;
                }
                roomNumber = res.roomNumber;
                found = 1;
               
                continue;
            }
            
            fprintf(temp, "%d,%s,%s,%s,%d,%s,%s,%.2f,%d\n",
                    res.reservationID, res.guestName, res.email, res.phone,
                    res.roomNumber, res.checkInDate, res.checkOutDate,
                    res.totalPrice, res.status);
        }
    }
    
    fclose(file);
    fclose(temp);
    
    if (found) {
        remove("data/reservations.txt");
        rename("data/reservations_temp.txt", "data/reservations.txt");
        
        
        if (wasConfirmed) {
            updateRoomOccupancy(roomNumber, 0);
            printf("✓ Room #%d marked as available.\n", roomNumber);
        }
        
        printf("✓ Reservation #%d deleted permanently!\n", deleteID);
    } else {
        remove("data/reservations_temp.txt");
        printf("✗ Reservation ID %d not found.\n", deleteID);
    }
}


int manageReservations(void) {
    int choice;
    
  
    reservationCounter = getHighestReservationID();
    
    while (1) {
        displayReservationMenu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                addReservation();
                break;
            case 2:
                viewReservations();
                break;
            case 3:
                searchReservation();
                break;
            case 4:
                updateReservationStatus();
                break;
            case 5:
                cancelReservation();
                break;
            case 6:
                deleteReservation();
                break;
            case 7:
                return 0;
            default:
                printf("✗ Invalid option. Please try again.\n");
        }
        saveContinue();
    }
    return 0;
}