#ifndef CUSTOMERMANAGEMENT_H
#define CUSTOMERMANAGEMENT_H
#include "Customer.h"
#include <unordered_map>

using namespace std;
class CustomerManagement {
	private:
		unordered_map<string, Customer> _customers;

	public:
		// Construct
		CustomerManagement();

		// Method
		void createAccount(string phoneNumber, string name);
		void displayCustomer(Customer *customer);
		void displayAllCustomers();
		
		void depositMoney(float money, Customer *customer); 	// Deposit monney from customer, Don't allow enter monney < 0
		// function helper
		Customer *findCustomerByPhoneNumber(string phoneNumber);

		// File Manager
		unordered_map<string, Customer> &getCustomers();

		void loadCustomer(string phoneNumber, string name,float balance );
};

#endif
