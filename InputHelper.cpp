
#include "InputHelper.h"

#include <iostream>
#include <sstream>
#include <cctype>
#include <cmath>
#include <cstdlib>

using namespace std;

// Read an integer within a specified range
int readInt(string message, int minValue, int maxValue) {
    string line;
    int value;
    char extra;

    while (true) {
        cout << message;

        if (!getline(cin, line)) {
            cout << "\nInput stream closed. Exiting.\n";
            exit(1);
        }

        stringstream ss(line);

        if (ss >> value &&
            !(ss >> extra) &&
            value >= minValue &&
            value <= maxValue) {
            return value;
        }

        cout << "Invalid input! Enter an integer from "
             << minValue << " to " << maxValue << ".\n";
    }
}

// Read a positive amount of money
float readPositiveMoney(string message) {
    string line;
    float money;
    char extra;

    while (true) {
        cout << message;

        if (!getline(cin, line)) {
            cout << "\nInput stream closed. Exiting.\n";
            exit(1);
        }

        stringstream ss(line);

        if (ss >> money &&
            !(ss >> extra) &&
            isfinite(money) &&
            money > 0) {
            return money;
        }

        cout << "Invalid amount! Enter a number greater than 0.\n";
    }
}

// Read phone number: digits only
string readPhoneNumber() {
    string phone;

    while (true) {
        cout << "Enter phone number: ";

        if (!getline(cin, phone)) {
            cout << "\nInput stream closed. Exiting.\n";
            exit(1);
        }

        bool valid = !phone.empty();

        for (char c : phone) {
            if (!isdigit(static_cast<unsigned char>(c))) {
                valid = false;
                break;
            }
        }

        if (valid) {
            return phone;
        }

        cout << "Invalid phone number! Use digits only.\n";
    }
}

// Read a non-empty customer name
string readCustomerName() {
    string name;

    while (true) {
        cout << "Enter customer name: ";

        if (!getline(cin, name)) {
            cout << "\nInput stream closed. Exiting.\n";
            exit(1);
        }

        bool hasCharacter = false;

        for (char c : name) {
            if (!isspace(static_cast<unsigned char>(c))) {
                hasCharacter = true;
                break;
            }
        }

        if (hasCharacter) {
            return name;
        }

        cout << "Name cannot be empty!\n";
    }
}

// Read and normalize seat ID: a1 -> A1
string readSeatID() {
    string seatID;

    while (true) {
        cout << "Enter seat ID (A1-E6): ";

        if (!getline(cin, seatID)) {
            cout << "\nInput stream closed. Exiting.\n";
            exit(1);
        }

        if (seatID.size() == 2) {
            seatID[0] = static_cast<char>(
                toupper(static_cast<unsigned char>(seatID[0]))
            );

            if (seatID[0] >= 'A' &&
                seatID[0] <= 'E' &&
                seatID[1] >= '1' &&
                seatID[1] <= '6') {
                return seatID;
            }
        }

        cout << "Invalid seat ID! Valid seats are A1 to E6.\n";
    }
}
