#include "SeatManagement.h"
#include <iostream>
#include <vector>

using namespace std;

SeatManagement::SeatManagement() {
	headWaitList = tailWaitList = nullptr;
	initSeatsMap_HashMap();
}

void SeatManagement::initSeatsMap_HashMap() {
	for (char row = 'A'; row <= 'E'; row++) {
		for (int i = 1; i <= 6; i++) {
			string seatID = row + to_string(i);
			string seatClass = "";
			char status = 'A'; // A: Avaible
			float seatPrice = 0.0;
			// A, B : Normal Seat
			// Price = 100
			if (row == 'A' || row == 'B') {
				seatClass = "Normal";
				seatPrice = 100;
			}
			// C, D : VIP Seat
			// Price = 200
			else if (row == 'C' || row == 'D') {
				seatClass = "VIP";
				seatPrice = 200;
			} else {
				seatClass = "Couple";
				seatPrice = 250;
			}

			Seat seat(seatID, seatClass, status, seatPrice); // Create object seat
			_seatMap[seatID] = seat;						 // Add to _seatMap
		}
	}
}

void SeatManagement::displaySeatMap() {
	cout << "\n	 -----------SEAT MAP----------- 		\n\n";

	for (char row = 'A'; row <= 'E'; row++) {
		cout << "  ";

		for (int number = 1; number <= 6; number++) {
			string seatID = string(1, row) + to_string(number);

			Seat &seat = _seatMap.at(seatID);

			cout << seat.getSeatID() << "[" << seat.getStatus() << "]   ";
		}

		cout << endl;
	}

	cout << "\n";
	cout << "A = Available\n";
	cout << "P = Pending\n";
	cout << "O = Ordered\n";

	cout << "\n";
	cout << "A1 -> B6 : Normal seats (100)\n";
	cout << "C1 -> D6 : VIP seats (200)\n";
	cout << "E1 -> E6 : Couple seats (250)\n";
}

// -----------------1. Order seat-------------------
void SeatManagement::orderSeats(vector<string> seatIDs, Customer *customer) {
    if (customer == nullptr) {
        cout << "Customer not found!\n";
        return;
    }

    if (seatIDs.empty()) {
        cout << "No seats selected!\n";
        return;
    }

    vector<string> orderedSeats;

    for (int i = 0; i < seatIDs.size(); i++) {
        string seatID = seatIDs[i];

        // Check duplicate seat IDs in this request
        bool duplicate = false;

        for (int j = 0; j < orderedSeats.size(); j++) {
            if (orderedSeats[j] == seatID) {
                duplicate = true;
                break;
            }
        }

        if (duplicate) {
            cout << seatID << " was entered more than once!\n";
            continue;
        }

        // Find seat in Hash Map
        auto it = _seatMap.find(seatID);

        if (it == _seatMap.end()) {
            cout << seatID << " does not exist!\n";
            continue;
        }

        Seat &seat = it->second;

        // Check seat status
        if (seat.getStatus() != 'A') {
            cout << seatID << " is PENDING or ORDERED!\n";
            continue;
        }

        // Add seat to Pending Linked List
        addToPendingList(seatID, customer);

        // Update seat information
        seat.setPhoneNumber(customer->getPhoneNumber());
        seat.setStatus('P');

        orderedSeats.push_back(seatID);

        cout << seatID << " ordered successfully!\n";
    }

    cout << "\n========== ORDER SUMMARY ==========\n";
    cout << "Customer Name : "
         << customer->getNameCustomer() << endl;
    cout << "Phone Number  : "
         << customer->getPhoneNumber() << endl;

    if (orderedSeats.empty()) {
        cout << "No seats were ordered successfully.\n";
    } else {
        cout << "Number of seats ordered: "
             << orderedSeats.size() << endl;

        cout << "Seats: ";

        for (int i = 0; i < orderedSeats.size(); i++) {
            cout << orderedSeats[i];

            if (i < orderedSeats.size() - 1) {
                cout << ", ";
            }
        }

        cout << "\n";
    }

    cout << "===================================\n";
}
//------------- Delete Node ------------------//

void SeatManagement::deleteNode(string seatID, string phoneNumber) {
	Node *prev = nullptr;
	Node *cur = headWaitList;

	while (cur != nullptr) {
		if (cur->seatID == seatID && cur->customer.getPhoneNumber() == phoneNumber) {
			// Delete HEAD
			if (cur == headWaitList) {
				headWaitList = cur->next;

				// List becomes empty
				if (headWaitList == nullptr) {
					tailWaitList = nullptr;
				}
			} else {
				// Delete MIDDLE or TAIL
				prev->next = cur->next;

				// Delete TAIL
				if (cur == tailWaitList) {
					tailWaitList = prev;
				}
			}

			delete cur;
			return;
		}

		prev = cur;
		cur = cur->next;
	}
}
// --------------------------2. Cancel seat ---------------------
void SeatManagement::cancelSeat(Customer *customer) {
	vector<string> listSeatPending;
	string phoneNumber = customer->getPhoneNumber();

	// 1. Find all pending seats of this customer
	Node *cur = headWaitList;

	while (cur != nullptr) {
		if (cur->customer.getPhoneNumber() == phoneNumber) {
			listSeatPending.push_back(cur->seatID);
		}

		cur = cur->next;
	}

	// 2. No pending seat
	if (listSeatPending.empty()) {
		cout << "\nYou have no pending seats to cancel!\n";
		return;
	}

	// 3. Display customer's pending seats
	cout << "\n========== YOUR PENDING SEATS ==========\n";

	for (int i = 0; i < listSeatPending.size(); i++) {
		string seatID = listSeatPending[i];

		auto it = _seatMap.find(seatID);

		if (it != _seatMap.end()) {
			Seat &seat = it->second;

			cout << "[" << i + 1 << "] "
			     << seat.getSeatID()
			     << " | " << seat.getSeatClass()
			     << " | Price: " << seat.getSeatPrice()
			     << endl;
		}
	}

	cout << "0. Cancel operation\n";
	cout << "========================================\n";

	// 4. Enter ticket numbers
	cout << "Enter ticket numbers to cancel (example: 1 2 3): ";

	vector<int> userChoice;
	int choice;

	while (cin >> choice) {
		if (choice == 0) {
			cout << "Cancel operation stopped.\n";
			return;
		}

		if (choice >= 1 && choice <= listSeatPending.size()) {
			userChoice.push_back(choice);
		} else {
			cout << "Invalid ticket number: " << choice << endl;
		}

		// Stop input when user presses Enter
		if (cin.peek() == '\n') {
			break;
		}
	}

	// 5. Cancel selected seats
	for (int i = 0; i < userChoice.size(); i++) {
		string seatID = listSeatPending[userChoice[i] - 1];

		auto it = _seatMap.find(seatID);

		if (it != _seatMap.end()) {
			Seat &seat = it->second;

			// P -> A
			seat.setStatus('A');
			seat.setPhoneNumber("");

			// Remove from linked list
			deleteNode(seatID, phoneNumber);

			cout << seatID << " cancelled successfully!\n";
		}
	}
}

void SeatManagement::addToPendingList(string seatID, Customer *customer) {
	Node *newNode = new Node(*customer, seatID);

	if (headWaitList == nullptr) {
		headWaitList = newNode;
		tailWaitList = newNode;
	} else {
		tailWaitList->next = newNode;
		tailWaitList = newNode;
	}
}

// ------------------------3. Display Awaiting Payment List (Linked List) -----------

void SeatManagement::displayAllPendingList() {
	if (headWaitList == nullptr) {
		cout << "\n========== AWAITING PAYMENT LIST ==========\n";
		cout << "No customer is waiting for payment.\n";
		return;
	}

	Node *cur = headWaitList;

	cout << "\n========== AWAITING PAYMENT LIST ==========\n";

	int count = 1;

	while (cur != nullptr) {
		cout << "\n[" << count << "]\n";
		cout << "Phone Number : " << cur->customer.getPhoneNumber() << endl;
		cout << "Customer Name: " << cur->customer.getNameCustomer() << endl;

		cout << "Seat ID      : " << cur->seatID << endl;

		auto it = _seatMap.find(cur->seatID);

		if (it != _seatMap.end()) {
			Seat &seat = it->second;

			cout << "Seat Class   : " << seat.getSeatClass() << endl;
			cout << "Seat Price   : " << seat.getSeatPrice() << endl;
			cout << "Status       : " << seat.getStatus() << endl;
		}

		cur = cur->next;
		count++;
	}

	cout << "\n===========================================\n";
}

// --------------------------- 4. Payment Confirmation -----------------------------
void SeatManagement::paymentTicketConfirm(Customer *customer) {
	vector<string> listSeatPending;

	string phoneNumber = customer->getPhoneNumber();

	Node *cur = headWaitList;

	// 1. Find all pending seats of customer
	while (cur != nullptr) {
		if (cur->customer.getPhoneNumber() == phoneNumber) {
			listSeatPending.push_back(cur->seatID);
		}

		cur = cur->next;
	}

	// 2. No pending seat
	if (listSeatPending.empty()) {
		cout << "\nYou have no pending tickets!\n";
		return;
	}

	// 3. Display pending tickets
	cout << "\n========== YOUR PENDING TICKETS ==========\n";

	for (int i = 0; i < listSeatPending.size(); i++) {
		string seatID = listSeatPending[i];

		auto it = _seatMap.find(seatID);

		if (it != _seatMap.end()) {
			Seat &seat = it->second;

			cout << "[" << i + 1 << "] "
			     << seat.getSeatID()
			     << " | " << seat.getSeatClass()
			     << " | Price: " << seat.getSeatPrice()
			     << endl;
		}
	}

	cout << "0. Cancel operation\n";
	cout << "===========================================\n";

	// 4. Enter ticket numbers
	cout << "Enter ticket numbers to confirm (example: 1 2 3): ";

	vector<int> choices;
	int choice;

	while (cin >> choice) {
		if (choice == 0) {
			cout << "Payment operation stopped.\n";
			return;
		}

		if (choice >= 1 && choice <= listSeatPending.size()) {
			choices.push_back(choice);
		} else {
			cout << "Invalid ticket number: " << choice << endl;
		}

		if (cin.peek() == '\n') {
			break;
		}
	}

	// 5. Calculate total money
	float totalMoney = 0.0;

	for (int i = 0; i < choices.size(); i++) {
		string seatID = listSeatPending[choices[i] - 1];

		auto it = _seatMap.find(seatID);

		if (it != _seatMap.end()) {
			totalMoney += it->second.getSeatPrice();
		}
	}

	cout << "\nTotal payment: " << totalMoney << endl;

	// 6. Print customerBalance
	float customerBalance = customer->getAccountBalance();

	if (customerBalance < totalMoney) {
		cout << "Your current balance not enought money !\n";
		return;
	}
	// 7. Payment successful
	cout << "\nPayment successful!\n";

	// 8. P -> O and remove from Pending List
	for (int i = 0; i < choices.size(); i++) {
		string seatID = listSeatPending[choices[i] - 1];

		auto it = _seatMap.find(seatID);

		if (it != _seatMap.end()) {
			Seat &seat = it->second;

			// P -> O
			seat.setStatus('O');

			// Remove from Pending Linked List
			deleteNode(seatID, phoneNumber);

			cout << seatID << " -> Ordered\n";
		}
	}

	float deductMoney = customerBalance - totalMoney;
	customer->setAccountBalance(deductMoney);
	cout << "Balance remaing : " << customer->getAccountBalance();
}
//------------------------ 5. Print Ticket ---------------
void SeatManagement::printTicket(Customer *customer) {
	string phoneNumber = customer->getPhoneNumber();

	bool found = false;

	cout << "\n============ TICKET ================\n";

	for (auto &pair : _seatMap) {
		Seat &seat = pair.second;

		// Find all ordered seats of this customer
		if (seat.getStatus() == 'O' && seat.getPhoneNumber() == phoneNumber) {
			found = true;

			cout << "Your Name    : " << customer->getNameCustomer() << endl;
			cout << "Phone Number : " << phoneNumber << endl;
			cout << "Seat ID      : " << seat.getSeatID() << endl;
			cout << "Seat Class   : " << seat.getSeatClass() << endl;
			cout << "Seat Price   : " << seat.getSeatPrice() << endl;
			cout << "Status       : Ordered" << endl;
			cout << "-----------------------------------\n";
		}
	}

	if (!found) {
		cout << "You don't have any seat ordered!\n";
	}

	cout << "====================================\n";
}
// ----------- LOAD File from txt --------------------
unordered_map<string, Seat> &SeatManagement::getSeatMap() {
	return _seatMap;
}