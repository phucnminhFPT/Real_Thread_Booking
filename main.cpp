#include <iostream>
#include "SeatManagement.h"
#include "CustomerManagement.h"
#include "FileManager.h"

using namespace std;

enum MenuChoice {
	ORDER_SEAT = 1,
	CANCEL_SEAT,

	DISPLAY_PENDING_LIST,
	PAYMENT_CONFIRMATION,
	PRINT_TICKET,

	CREATE_ACCOUNT,
	SHOW_ONE_CUSTOMER_INFORMATION,
	SHOW_ACCOUNT_BALANCE,
	DEPOSIT_MONEY,

	EXIT
};

void Menu() {
	cout << "\n---------------- Booking --------------\n";
	cout << "1. Order seat\n";	// Add last seat into Pending list
	cout << "2. Cancel seat\n"; // Remove seat from Pending list

	cout << "\n---------------- PAYMENT --------------\n";
	cout << "3. Display All Pending List (Linked List)\n"; // Display all customers have pending seat
	cout << "4. Payment Confirmation\n";				   // Confirm and pay seat. 'P' become 'O'
	cout << "\n---------------- TICKET ---------------\n";
	cout << "5. Print Ticket\n";

	cout << "\n--------------- CUSTOMER ---------------\n";
	cout << "6. Create account\n";
	cout << "7. Show Customer Information\n";
	cout << "8. Show Account Balance\n";
	cout << "9. Deposit Money\n";

	cout << "\n10. Exit\n";
}
string enterSeatID() {
	cout << "\nEnter SeatID : ";
	string seatID = "";
	cin >> seatID;

	return seatID;
}

string enterPhoneNumber() {
	cout << "\nEnter Number Phone : ";
	string numberPhone = "";
	cin >> numberPhone;

	return numberPhone;
}

string enterNameCustomer() {
	cout << "\nEnter your name : ";
	string nameCustomer = "";
	cin.ignore();
	getline(cin, nameCustomer);
	return nameCustomer;
}
int main() {

	int choice = 0;
	SeatManagement sM;
	CustomerManagement cM;

	FileManager fileManager("BookingData.txt");

	// Load saved data
	fileManager.load(cM, sM);
	while (choice != EXIT) {
		Menu(); // Print menu
		cout << "Enter your choice : ";
		cin >> choice;
		switch (choice) {
			case ORDER_SEAT: {
				// 1. Order seat
				sM.displaySeatMap();
				// 1. Enter number phone and find number
				string phoneNumber = enterPhoneNumber();
				Customer *customer = cM.findCustomerByPhoneNumber(phoneNumber);
				if (customer == nullptr) {
					cout << "Customer not found!\n";
					cout << "Please create an account first.\n";
					break;
				}

				// 2. Enter seatID
				string seatID = enterSeatID();

				sM.orderSeat(seatID, customer);

				break;
			}
			// 2. Cancel seat
			case CANCEL_SEAT: {
				string phoneNumber = enterPhoneNumber();
				Customer *customer = cM.findCustomerByPhoneNumber(phoneNumber);
				if (customer == nullptr) {
					cout << "Customer not found!\n";
					cout << "Please create an account first.\n";
					break;
				}
				sM.cancelSeat(customer);
				break;
			}
			// 3. Display All Pending List (Linked List)
			case DISPLAY_PENDING_LIST: {
				sM.displayAllPendingList();
				break;
			}
			// 4. Payment Confirmation
			case PAYMENT_CONFIRMATION: {
				string phoneNumber = enterPhoneNumber();
				Customer *customer = cM.findCustomerByPhoneNumber(phoneNumber);
				if (customer == nullptr) {
					cout << "Customer not found!\n";
					cout << "Please create an account first.\n";
					break;
				}

				sM.paymentTicketConfirm(customer);
				break;
			}
			// 6. Create account
			case CREATE_ACCOUNT: {
				string numberPhone = enterPhoneNumber();
				string name = enterNameCustomer();
				cM.createAccount(numberPhone, name);
				break;
			}

			// 9. Deposit Money
			case DEPOSIT_MONEY: {
				string phoneNumber = enterPhoneNumber();
				Customer *customer = cM.findCustomerByPhoneNumber(phoneNumber);
				if (customer == nullptr) {
					cout << "Customer not found!\n";
					cout << "Please create an account first.\n";
					break;
				}
				float money = 0.0;
				cout << "Enter money to deposit : ";
				cin >> money;
				cM.depositMoney(money, customer);
				break;
			}
			case EXIT: {
				// Luu lai vao TXT
				cout << "Thank you and good bye\n";
				cout << "File was saved (*)\n";
				fileManager.save(cM, sM);
				break;
			}
			default: {
				cout << "Invalid choice , choice again ! \n";
				break;
			}
		}
	}

	return 0;
}
