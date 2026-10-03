#include "SeatManagement.h"
#include <iostream>
#include <vector>

using namespace std;

SeatManagement::SeatManagement()
{
	headWaitList = tailWaitList = nullptr;
	initSeatsMap_HashMap();
}

void SeatManagement::initSeatsMap_HashMap()
{
	for (char row = 'A'; row <= 'E'; row++)
	{
		for (int i = 1; i <= 6; i++)
		{
			string seatID = row + to_string(i);
			string seatClass = "";
			char status = 'A'; // A: Avaible
			float seatPrice = 0.0;
			// A, B : Normal Seat
			// Price = 100
			if (row == 'A' || row == 'B')
			{
				seatClass = "Normal";
				seatPrice = 100;
			}
			// C, D : VIP Seat
			// Price = 200
			else if (row == 'C' || row == 'D')
			{
				seatClass = "VIP";
				seatPrice = 200;
			}
			else
			{
				seatClass = "Couple";
				seatPrice = 250;
			}

			Seat seat(seatID, seatClass, status, seatPrice); // Create object seat
			_seatMap[seatID] = seat;						 // Add to _seatMap
		}
	}
}

void SeatManagement::displaySeatMap()
{
	cout << "\n------------SEAT MAP----------- \n\n";

	for (char row = 'A'; row <= 'E'; row++)
	{
		cout << "  ";

		for (int number = 1; number <= 6; number++)
		{
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
void SeatManagement::orderSeat(string seatID, Customer *customer)
{
	// Find seat
	auto it = _seatMap.find(seatID);

	// 1. Seat does not exist
	if (it == _seatMap.end())
	{
		cout << seatID << " not existing !";
		return;
	}

	Seat &seat = it->second; // Get value
	// 2.1 If P : Pending
	if (seat.getStatus() == 'P')
	{
		cout << "This seat is PENDING !";
		return;
	}

	// 2.2 If O : Ordered
	if (seat.getStatus() == 'O')
	{
		cout << "This seat was ORDERED !";
		return;
	}

	// 3. Add customer to pending payment list
	addToPendingList(seatID, customer);

	cout << seatID << " ordered success ! Added to Pending List";

	// 4. Change status, add numberPhone
	seat.setPhoneNumber(customer->getPhoneNumber());
	seat.setStatus('P');
}

// ------------------*2. Function Support for cancelSeat --------------------
void SeatManagement::displayCustomerSeats(string phoneNumber)
{
	bool found = false;

	cout << "\n========== YOUR SEATS ==========\n";

	for (auto &pair : _seatMap)
	{
		Seat &seat = pair.second;

		if (seat.getPhoneNumber() == phoneNumber &&
			(seat.getStatus() == 'P' || seat.getStatus() == 'O'))
		{
			cout << "Seat ID : " << seat.getSeatID()
				 << " | Class : " << seat.getSeatClass()
				 << " | Price : " << seat.getSeatPrice()
				 << " | Status : " << seat.getStatus()
				 << endl;

			found = true;
		}
	}

	if (!found)
	{
		cout << "You don't have any seat to cancel.\n";
	}

	cout << "================================\n";
}

// --------------------------2. Cancel seat ---------------------
void SeatManagement::cancelSeat(string seatID, Customer *customer)
{
	// 1. Find seat
	auto it = _seatMap.find(seatID);

	if (it == _seatMap.end())
	{
		cout << "Seat " << seatID << " does not exist!\n";
		return;
	}

	Seat &seat = it->second;

	// 2. Check if this seat belongs to this customer
	if (seat.getPhoneNumber() != customer->getPhoneNumber())
	{
		cout << "This seat does not belong to you!\n";
		return;
	}

	// 3. Check if seat is Pending
	if (seat.getStatus() != 'P')
	{
		cout << "This seat is not Pending!\n";
		return;
	}

	// 4. Delete corresponding node from Pending List
	Node *cur = headWaitList;
	Node *prev = nullptr;

	while (cur != nullptr)
	{
		if (cur->seatID == seatID && cur->customer.getPhoneNumber() == customer->getPhoneNumber())
		{
			// Case 1: Delete first node
			if (prev == nullptr)
			{
				headWaitList = cur->next;
			}
			// Case 2: Delete middle or last node
			else
			{
				prev->next = cur->next;
			}

			// If deleting tail node
			if (cur == tailWaitList)
			{
				tailWaitList = prev;
			}

			delete cur;

			// If list becomes empty
			if (headWaitList == nullptr)
			{
				tailWaitList = nullptr;
			}

			break;
		}

		prev = cur;
		cur = cur->next;
	}

	// 5. Change seat from Pending -> Available
	seat.setStatus('A');

	// 6. Remove customer phone number from seat
	seat.setPhoneNumber("");

	cout << "Cancel Pending Seat successfully!\n";
	cout << "Seat " << seatID << " is now AVAILABLE.\n";
}

void SeatManagement::addToPendingList(string seatID, Customer *customer)
{
	Node *newNode = new Node(*customer, seatID);

	if (headWaitList == nullptr)
	{
		headWaitList = newNode;
		tailWaitList = newNode;
	}
	else
	{
		tailWaitList->next = newNode;
		tailWaitList = newNode;
	}
}

// ------------------------3. Display Awaiting Payment List (Linked List) -----------

void SeatManagement::displayAllPendingList()
{
	if (headWaitList == nullptr)
	{
		cout << "\n========== AWAITING PAYMENT LIST ==========\n";
		cout << "No customer is waiting for payment.\n";
		return;
	}

	Node *cur = headWaitList;

	cout << "\n========== AWAITING PAYMENT LIST ==========\n";

	int count = 1;

	while (cur != nullptr)
	{
		cout << "\n[" << count << "]\n";
		cout << "Phone Number : " << cur->customer.getPhoneNumber() << endl;
		cout << "Customer Name: " << cur->customer.getNameCustomer() << endl;

		cout << "Seat ID      : " << cur->seatID << endl;

		auto it = _seatMap.find(cur->seatID);

		if (it != _seatMap.end())
		{
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
void SeatManagement::paymentTicketConfirm(Customer *customer)
{
	vector<string> listSeatPending;

	string phoneNumber = customer->getPhoneNumber();

	Node *cur = headWaitList;

	while (cur != nullptr)
	{
		if (cur->customer.getPhoneNumber() == phoneNumber)
		{

			auto it = _seatMap.find();
			listSeatPending.push_back(cur->seatID);
		}
		cur = cur->next;
	}
}