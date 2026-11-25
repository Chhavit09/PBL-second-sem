Hotel Reservation System
Overview
The Hotel Reservation System is a comprehensive application designed to manage hotel reservations efficiently. It includes features for secure staff authentication, reservation management, search functionality, sorting, cancellation, and report generation.

Features
Secure Authentication: Staff can log in using secure credentials.
Reservation Management: Add, modify, and delete reservations.
Search Functionality: Search reservations by guest name or room number.
Sorting: Sort reservations by check-in date or room type.
Cancellation: Cancel reservations using reservation ID.
Reports: Generate reports on room occupancy, total reservations, and revenue.
Project Structure
hotel-reservation-system
├── src
│   ├── main.c
│   ├── admin.c
│   ├── auth.c
│   ├── reservations.c
│   ├── search.c
│   ├── sort.c
│   ├── cancellation.c
│   ├── reports.c
│   └── utils.c
├── include
│   ├── admin.h
│   ├── auth.h
│   ├── reservations.h
│   ├── search.h
│   ├── sort.h
│   ├── cancellation.h
│   ├── reports.h
│   ├── structures.h
│   └── utils.h
├── data
│   ├── staff_credentials.txt
│   ├── reservations.txt
│   └── reports.txt
├── Makefile
└── README.md
Setup Instructions
Clone the repository to your local machine.
Navigate to the project directory.
Compile the project using the provided Makefile:
make
Run the application:
./hotel-reservation-system
Usage Guidelines
Staff must log in using their credentials stored in data/staff_credentials.txt.
Use the main menu to navigate through different functionalities.
Follow prompts for adding, searching, or cancelling reservations.
Contribution
Contributions are welcome! Please fork the repository and submit a pull request for any enhancements or bug fixes.

License
This project is licensed under the MIT License. See the LICENSE file for details.
