#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "auth.h"
#include "utils.h"

int authenticateUser(void) {
    displayLoginMenu();
    return 1;
}

int validateCredentials(const char *username, const char *password) {
    FILE *file = fopen("data/credentials.txt", "r");
    if (file == NULL) {
        return 0;
    }

    char fileUsername[MAX_USERNAME_LENGTH];
    char filePassword[MAX_PASSWORD_LENGTH];
    
    while (fscanf(file, "%49s %49s", fileUsername, filePassword) != EOF) {
        if (strcmp(username, fileUsername) == 0 && strcmp(password, filePassword) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

void displayLoginMenu(void) {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int attempts = 3;

    printf("\n");
    displayHeader("=== HOTEL MANAGEMENT SYSTEM LOGIN ===");
    
    while (attempts > 0) {
        printf("\nEnter username: ");
        scanf("%49s", username);
        printf("Enter password: ");
        scanf("%49s", password);

        if (validateCredentials(username, password)) {
            printf("\nLogin successful! Welcome %s\n", username);
            return;
        } else {
            attempts--;
            if (attempts > 0)
                printf("Invalid credentials. %d attempts remaining.\n", attempts);
            else {
                printf("Login failed. Exiting system.\n");
                exit(1);
            }
        }
    }
}

void registerNewUser(void) {
    FILE *file = fopen("data/credentials.txt", "a");
    if (file == NULL) {
        printf("Error opening credentials file.\n");
        return;
    }

    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("\n=== NEW USER REGISTRATION ===\n");
    printf("Enter new username: ");
    scanf("%49s", username);
    printf("Enter new password: ");
    scanf("%49s", password);

    fprintf(file, "%s %s\n", username, password);
    fflush(file);
    fclose(file);
    printf("User registered successfully!\n");
}

void viewAllStaff(void) {
    printf("\n");
    displayHeader("=== ALL STAFF MEMBERS ===");
    
    FILE *file = fopen("data/staff_credential.txt", "r");
    if (file == NULL) {
        printf("No staff members found.\n");
        return;
    }

    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int count = 0;
    
    printf("%-20s | %-20s\n", "Username", "Password");
    printf("------------------------------------------\n");
    
    while (fscanf(file, "%49s %49s", username, password) != EOF) {
        printf("%-20s | %-20s\n", username, password);
        count++;
    }
    
    fclose(file);
    printf("\nTotal Staff: %d\n", count);
}

void addStaff(void) {
    printf("\n=== ADD NEW STAFF MEMBER ===\n");
    
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    
    printf("Enter staff username: ");
    scanf("%49s", username);
    printf("Enter staff password: ");
    scanf("%49s", password);
    
    FILE *file = fopen("data/staff_credential.txt", "a");
    if (file == NULL) {
        printf("Error opening staff file.\n");
        return;
    }
    
    fprintf(file, "%s %s\n", username, password);
    fflush(file);
    fclose(file);
    printf("✓ Staff member '%s' added successfully!\n", username);
}

void deleteStaff(void) {
    printf("\n=== DELETE STAFF MEMBER ===\n");
    
    char targetUsername[MAX_USERNAME_LENGTH];
    printf("Enter staff username to delete: ");
    scanf("%49s", targetUsername);
    
    FILE *file = fopen("data/staff_credential.txt", "r");
    FILE *temp = fopen("data/staff_temp.txt", "w");
    
    if (file == NULL || temp == NULL) {
        printf("Error opening file.\n");
        return;
    }
    
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int found = 0;
    
    while (fscanf(file, "%49s %49s", username, password) != EOF) {
        if (strcmp(username, targetUsername) == 0) {
            found = 1;
        } else {
            fprintf(temp, "%s %s\n", username, password);
        }
    }
    
    fclose(file);
    fclose(temp);
    
    if (found) {
        remove("data/staff_credential.txt");
        rename("data/staff_temp.txt", "data/staff_credential.txt");
        printf("✓ Staff member '%s' deleted successfully!\n", targetUsername);
    } else {
        remove("data/staff_temp.txt");
        printf("✗ Staff member '%s' not found.\n", targetUsername);
    }
}

void updateStaffPassword(void) {
    printf("\n=== UPDATE STAFF PASSWORD ===\n");
    
    char targetUsername[MAX_USERNAME_LENGTH];
    char newPassword[MAX_PASSWORD_LENGTH];
    printf("Enter staff username: ");
    scanf("%49s", targetUsername);
    printf("Enter new password: ");
    scanf("%49s", newPassword);
    
    FILE *file = fopen("data/staff_credential.txt", "r");
    FILE *temp = fopen("data/staff_temp.txt", "w");
    
    if (file == NULL || temp == NULL) {
        printf("Error opening file.\n");
        return;
    }
    
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int found = 0;
    
    while (fscanf(file, "%49s %49s", username, password) != EOF) {
        if (strcmp(username, targetUsername) == 0) {
            fprintf(temp, "%s %s\n", username, newPassword);
            found = 1;
        } else {
            fprintf(temp, "%s %s\n", username, password);
        }
    }
    
    fclose(file);
    fclose(temp);
    
    if (found) {
        remove("data/staff_credential.txt");
        rename("data/staff_temp.txt", "data/staff_credential.txt");
        printf("✓ Password updated successfully for '%s'!\n", targetUsername);
    } else {
        remove("data/staff_temp.txt");
        printf("✗ Staff member '%s' not found.\n", targetUsername);
    }
}
