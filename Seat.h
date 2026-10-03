#ifndef SEAT_H
#define SEAT_H

#include <string>
using namespace std;

class Seat {
	private:
		string _seatID;	   // A , B, C, D, E  1 -> 9
		string _seatClass; // 1: VIP       2: Normal       3: Couple
		char _status;	   // A: Available  O: Ordered      P: Pending
		float _seatPrice;  // 1: VIP = 200 2: Normal = 100 3: Couple = 250
		string _phoneNumber;

	public:
		// Construct init
		Seat();
		Seat(string seatID, string seatClass, char status, float seatPrice); // A: Avaiable ;  O: Ordered ;  P: Pending
		// Deconstruct init

		// Getter
		string getSeatID();
		string getSeatClass();
		char getStatus(); // A : avaiable , O : orderded , P : Pending
		float getSeatPrice();
		string getPhoneNumber();

		// Setter
		void setSeatID(string seatID);
		void setSeatClass(string seatClass);
		void setStatus(char status);
		void setSeatPrice(float seatPrice);
		void setPhoneNumber(string phoneNumber);
};

#endif