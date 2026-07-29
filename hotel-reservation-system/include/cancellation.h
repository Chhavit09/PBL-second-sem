#ifndef CANCELLATION_H
#define CANCELLATION_H

#include "structures.h"

// Function to cancel a reservation by reservation ID
int cancel_reservation(int reservation_id);

// Function to display cancellation confirmation
void display_cancellation_confirmation(int reservation_id);

#endif // CANCELLATION_H