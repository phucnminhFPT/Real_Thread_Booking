#ifndef SEATMANAGEMENT_H
#define SEATMANAGEMENT_H

#include "Seat.h"
#include "Customer.h"
#include <unordered_map>
class SeatManagement
{
private:
	// Hash Map
	unordered_map<string, Seat> _seatMap;

	// Single linked list
	struct Node
	{
		Customer customer;
		string seatID;

		Node *next;

		// Auto fill infor when it is called
		Node(Customer customer, string seatID)
		{
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

	// 1. Order seat
	void orderSeat(string seatID, Customer *customer);

	// 2. Cancel seat
	void cancelSeat(Customer *customer);

	// Add customer to waiting payment list
	void addToPendingList(string seatID, Customer *customer);

	// 3. Display waiting payment list
	void displayAllPendingList();

	// Display Customer Seats for cancelSeat
	void displayCustomerSeats(string phoneNumber);

	// Payment confirmation
	void paymentTicketConfirm(Customer *customer);
};
#endif