#include "CustomerManagement.h"
#include <iostream>
#include <cmath>
#include <limits>

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

// 7. Show your information
void CustomerManagement::displayCustomer(Customer *customer) {
	string phoneNumber = customer->getPhoneNumber();
	if (_customers.find(phoneNumber) != _customers.end()) {
		cout << "===== CUSTOMER INFORMATION =====" << endl;
		cout << "Phone Number : " << customer->getPhoneNumber() << endl;
		cout << "Name         : " << customer->getNameCustomer() << endl;
		cout << "Balance      : " << customer->getAccountBalance() << endl;
		return;
	}

	return;
		}
// -----------8. Show all customer information
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
	if (customer == nullptr) {
		cout << "Customer not found!\n";
		return;
	}

	if (!isfinite(money) || money <= 0) {
		cout << "Deposit amount must be greater than 0!\n";
		return;
	}

	float currentBalance = customer->getAccountBalance();

	// Prevent invalid balance and overflow
	if (!isfinite(currentBalance) ||
	        money > numeric_limits<float>::max() - currentBalance) {
		cout << "Invalid amount or balance overflow!\n";
		return;
	}

	if (!isfinite(money) || money <= 0) {
		cout << "Deposit amount must be greater than 0!\n";
		return;
	}

	float currentBalance = customer->getAccountBalance();

	// Prevent invalid balance and overflow
	if (!isfinite(currentBalance) ||
	        money > numeric_limits<float>::max() - currentBalance) {
		cout << "Invalid amount or balance overflow!\n";
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