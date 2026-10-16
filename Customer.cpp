#include <iostream>
#include "Customer.h"

using namespace std;

// Constructor and deconstructor
Customer::Customer() {
	_accountBalance = 0.0;
	_nameCustomer = "";
	_phoneNumber = ""; // Unique key
}

// Getter
float Customer::getAccountBalance() {
	return _accountBalance;
}
string Customer::getNameCustomer() {
	return _nameCustomer;
}
string Customer::getPhoneNumber() {
	return _phoneNumber;
}

// Setter
void Customer::setAccountBalance(float monney) {
	this->_accountBalance = monney;
}
void Customer::setNameCustomer(string nameCustomer) {
	this->_nameCustomer = nameCustomer;
}
void Customer::setPhoneNumber(string phoneNumber) {
	this->_phoneNumber = phoneNumber;
}