#include "CustomerManagement.h"
#include <iostream>

using namespace std;

// Constructor
CustomerManagement::CustomerManagement() {
}

// 6. Create a new customer
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

// Function Helper : Find customer by phone number
Customer *CustomerManagement::findCustomerByPhoneNumber(string phoneNumber) {
	auto it = _customers.find(phoneNumber);

	// Customer not found
	if (it == _customers.end()) {
		return nullptr;
	}

	// Return address of Customer
	return &(it->second);
}

// Display one customer
void CustomerManagement::displayCustomer(string phoneNumber) {
	Customer *customer = findCustomerByPhoneNumber(phoneNumber);

	if (customer == nullptr) {
		cout << "Customer not found!" << endl;
		return;
	}

	cout << "===== CUSTOMER INFORMATION =====" << endl;
	cout << "Phone Number : " << customer->getPhoneNumber() << endl;
	cout << "Name         : " << customer->getNameCustomer() << endl;
	cout << "Balance      : " << customer->getAccountBalance() << endl;
}

//------------- 8. Show Account Balance --------------//

void CustomerManagement::showAccountBalance(Customer *customer) {
	float money = customer->getAccountBalance();

	cout << "Your current account : " << money;
}

//------------------ 9. Deposit Money -------------//

void CustomerManagement::depositMoney(float money, Customer *customer) {
	if (money < 0) {
		cout << "Can't deposit negative monney\n";
		return;
	}

	float a = customer->getAccountBalance() + money;
	customer->setAccountBalance(a);

	Customer *b = customer;
	showAccountBalance(b);
}


// -------------------------- Load file --------------------
// Get all customers
unordered_map<string, Customer> &CustomerManagement::getCustomers() {
	return _customers;
}

// Load customer from file
// This function does NOT display any message
void CustomerManagement::loadCustomer( string phoneNumber, string name, float balance) {
	Customer customer;

	customer.setPhoneNumber(phoneNumber);
	customer.setNameCustomer(name);
	customer.setAccountBalance(balance);

	_customers[phoneNumber] = customer;
}