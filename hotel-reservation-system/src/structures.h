#ifndef STRUCTURES_H
#define STRUCTURES_H

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define MAX_GUEST_NAME_LENGTH 100
#define MAX_DATE_LENGTH 15
#define MAX_EMAIL_LENGTH 100
#define MAX_PHONE_LENGTH 20
#define MAX_ROOMS 100
#define MAX_RESERVATIONS 500


typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;


typedef struct {
    int roomNumber;
    char roomType[30]; 
    float price;
    int isOccupied;
} Room;


typedef struct {
    int reservationID;
    char guestName[MAX_GUEST_NAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char phone[MAX_PHONE_LENGTH];
    int roomNumber;
    char checkInDate[MAX_DATE_LENGTH];
    char checkOutDate[MAX_DATE_LENGTH];
    float totalPrice;
    int status; 
} Reservation;


typedef struct {
    int reservationID;
    float amount;
    char paymentDate[MAX_DATE_LENGTH];
    char paymentMethod[30];
} Payment;

#endif
