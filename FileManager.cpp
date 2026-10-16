#include "FileManager.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
using namespace std;

// Constructor
FileManager::FileManager(string fileName) {
	_fileName = fileName;
}

void FileManager::load(CustomerManagement &customerManagement,
                       SeatManagement &seatManagement) {
	ifstream file(_fileName);

	if (!file.is_open()) {
		cout << "No save file found. Starting with default data.\n";
		return;
	}

	string line;
	string section = "";

	while (getline(file, line)) {

		if (line.empty()) {
			continue;
		}

		// Detect section
		if (line == "[CUSTOMERS]") {
			section = "CUSTOMERS";
			continue;
		}

		if (line == "[SEATS]") {
			section = "SEATS";
			continue;
		}

		// ================= CUSTOMERS =================

		if (section == "CUSTOMERS") {

			string phone;
			string name;
			string balanceString;

			stringstream ss(line);

			getline(ss, phone, '|');
			getline(ss, name, '|');
			getline(ss, balanceString, '|');

			float balance = stof(balanceString);

			customerManagement.loadCustomer(
			    phone,
			    name,
			    balance
			);
		}

		// ================= SEATS =================

		else if (section == "SEATS") {

			string seatID;
			string seatClass;
			string statusString;
			string priceString;
			string phone;

			stringstream ss(line);

			getline(ss, seatID, '|');
			getline(ss, seatClass, '|');
			getline(ss, statusString, '|');
			getline(ss, priceString, '|');
			getline(ss, phone, '|');

			char status = statusString[0];
			float price = stof(priceString);

			auto &seats = seatManagement.getSeatMap();

			auto it = seats.find(seatID);

			if (it == seats.end()) {
				continue;
			}

			Seat &seat = it->second;

			// Restore seat information
			seat.setSeatID(seatID);
			seat.setSeatClass(seatClass);
			seat.setStatus(status);
			seat.setSeatPrice(price);
			seat.setPhoneNumber(phone);

			// Rebuild Pending Linked List
			if (status == 'P' && !phone.empty()) {

				Customer *customer =
				    customerManagement.findCustomerByPhoneNumber(phone);

				if (customer != nullptr) {
					seatManagement.addToPendingList(
					    seatID,
					    customer
					);
				}
			}
		}
	}

	file.close();

	cout << "Data loaded successfully!\n";
}

void FileManager::save(CustomerManagement &customerManagement, SeatManagement &seatManagement) {
	ofstream file(_fileName);

	if (!file.is_open()) {
		cout << "Cannot open file to save!\n";
		return;
	}

	// ================= CUSTOMERS =================

	file << "[CUSTOMERS]\n";

	unordered_map<string, Customer> &customers =
	    customerManagement.getCustomers();

	for (auto &pair : customers) {
		Customer &customer = pair.second;

		file << customer.getPhoneNumber() << "|"
		     << customer.getNameCustomer() << "|"
		     << customer.getAccountBalance() << "\n";
	}

	// ================= SEATS =================

	file << "\n[SEATS]\n";

	unordered_map<string, Seat> &seats =
	    seatManagement.getSeatMap();

	for (auto &pair : seats) {
		Seat &seat = pair.second;

		file << seat.getSeatID() << "|"
		     << seat.getSeatClass() << "|"
		     << seat.getStatus() << "|"
		     << seat.getSeatPrice() << "|"
		     << seat.getPhoneNumber() << "\n";
	}

	file.close();

	cout << "Data saved successfully!\n";
}