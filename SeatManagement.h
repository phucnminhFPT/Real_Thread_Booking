#ifndef SEATMANAGEMENT_H
#define SEATMANAGEMENT_H

#include "Seat.h"
#include "Customer.h"
#include <unordered_map>
#include <vector>
class SeatManagement {
	private:
		// Hash Map
		unordered_map<string, Seat> _seatMap;

		// Single linked list
		struct Node {
			Customer customer;
			string seatID;

			Node *next;

			// Auto fill infor when it is called
			Node(Customer customer, string seatID) {
				this->customer = customer;
				this->seatID = seatID;
				this->next = nullptr;
			}
		};

		Node *headWaitList;
		Node *tailWaitList;

	public:
		// Constructor and Destructor
		SeatManagement();

		// Initialize seat Hash Map
		void initSeatsMap_HashMap();

		// Display seat map
		void displaySeatMap();

		// 1. Order seats
		// Order multiple seats for one customer
		void orderSeats(vector<string> seatIDs, Customer *customer);
		// 2. Cancel seat
		void cancelSeat(Customer *customer);
		// 3. Display waiting payment list
		void displayAllPendingList();

		// 4. Payment Confirmation
		void paymentTicketConfirm(Customer *customer);
		// 5. Pring Ticket
		void printTicket (Customer *customer);
		// Helper function
		void addToPendingList(string seatID, Customer *customer);
		void displayCustomerSeats(string phoneNumber);
		void deleteNode(string seatID, string phoneNumber);

		// File Manager
		unordered_map<string, Seat> &getSeatMap();
};
#endif