#include "CustomerManagement.h"
#include <iostream>

using namespace std;

// Constructor
CustomerManagement::CustomerManagement() {}
// Helper Function findCustomer by
Customer *CustomerManagement::findCustomerByPhoneNumber(string phoneNumber) {
	auto it = _customers.find(phoneNumber);

	if (it != _customers.end()) {
		return &it->second;
	}

	return nullptr;
}

//------------------- 6. Create a new customer-----------------------//
void CustomerManagement::createAccount(string phoneNumber, string name) {
	// Check if phone number already exists
	if (_customers.find(phoneNumber) != _customers.end()) {
		cout << phoneNumber << " already exists ! Return main menu\n";
		return;
	}

	// Create new Customer
	Customer customer;

	customer.setPhoneNumber(phoneNumber);
	customer.setNameCustomer(name);
	customer.setAccountBalance(0.0);
	// Insert customer into Hash Table
	_customers[phoneNumber] = customer;

	cout << "Create success !\n";
	cout << "Your phone number : " << phoneNumber << endl;
	cout << "Your name :" << name << endl;
	cout << "Your current account : 0.0\n";
}

//------------------- 8.show info By Phone Number ----------------------//
void CustomerManagement::showInfoCustomerByPhoneNumber(Customer *customer, SeatManagement &sM) {
	if (customer == nullptr) {
		cout << "Customer not found!\n";
		return;
	}

	// 1. Display basic customer information
	cout << "\n========== CUSTOMER INFORMATION ==========\n";
	cout << "Phone Number : "
	     << customer->getPhoneNumber() << endl;
	cout << "Name         : "
	     << customer->getNameCustomer() << endl;
	cout << "Balance      : "
	     << customer->getAccountBalance() << endl;

	// 2. Get all seats
	unordered_map<string, Seat> &seats = sM.getSeatMap();

	int pendingCount = 0;
	int orderedCount = 0;
	float totalTicketPrice = 0.0;

	cout << "\n========== YOUR SEATS ==========\n";

	// 3. Find seats belonging to this customer
	for (auto &pair : seats) {
		Seat &seat = pair.second;

		if (seat.getPhoneNumber() != customer->getPhoneNumber()) {
			continue;
		}

		char status = seat.getStatus();

		// Only display Pending and Ordered seats
		if (status != 'P' && status != 'O') {
			continue;
		}

		cout << "\nSeat ID    : " << seat.getSeatID() << endl;
		cout << "Seat Class : " << seat.getSeatClass() << endl;
		cout << "Seat Price : " << seat.getSeatPrice() << endl;

		if (status == 'P') {
			cout << "Status     : Pending (Unpaid)\n";
			pendingCount++;
		} else if (status == 'O') {
			cout << "Status     : Ordered (Paid)\n";
			orderedCount++;
			totalTicketPrice += seat.getSeatPrice();
		}

		cout << "---------------------------------\n";
	}

	// 4. Display ticket summary
	cout << "\n========== TICKET SUMMARY ==========\n";
	cout << "Pending seats       : " << pendingCount << endl;
	cout << "Purchased seats     : " << orderedCount << endl;
	cout << "Total purchased cost: " << totalTicketPrice << endl;
	cout << "===================================\n";
}

// ------------------9. Show all customer information---------------//
void CustomerManagement::displayAllCustomers() {
	if (_customers.empty()) {
		cout << "\nNo customer existing!\n";
		return;
	}

	cout << "\n========== ALL CUSTOMER INFORMATION ==========\n";

	int count = 1;

	for (auto &pair : _customers) {
		Customer &customer = pair.second;

		cout << "\n[" << count << "]\n";
		cout << "Phone Number : " << customer.getPhoneNumber() << endl;
		cout << "Name         : " << customer.getNameCustomer() << endl;
		cout << "Balance      : " << customer.getAccountBalance() << endl;
		cout << "---------------------------------------------\n";

		count++;
	}

	cout << "==============================================\n";
}

//------------------ 9. Deposit Money -------------//

void CustomerManagement::depositMoney(float money, Customer *customer) {
	if (money < 0) {
		cout << "Can't deposit negative monney\n";
		return;
	}

	float a = customer->getAccountBalance() + money;
	customer->setAccountBalance(a);
	cout << "===== CUSTOMER INFORMATION =====" << endl;
	cout << "Phone Number : " << customer->getPhoneNumber() << endl;
	cout << "Name         : " << customer->getNameCustomer() << endl;
	cout << "Balance      : " << customer->getAccountBalance() << endl;
}

// -------------------------- Load file --------------------
// Get all customers
unordered_map<string, Customer> &CustomerManagement::getCustomers() {
	return _customers;
}

// Load customer from file
// This function does NOT display any message
void CustomerManagement::loadCustomer(string phoneNumber, string name, float balance) {
	Customer customer;

	customer.setPhoneNumber(phoneNumber);
	customer.setNameCustomer(name);
	customer.setAccountBalance(balance);

	_customers[phoneNumber] = customer;
}