#include "Seat.h"
#include <string>

// Constructor
Seat::Seat() {
	_seatID = "";
	_seatClass = "";
	_status = 'A'; // Available
	_seatPrice = 0.0;
	_phoneNumber ="";
}

Seat::Seat(string seatID, string seatClass, char status, float seatPrice) {
	_seatID = seatID;
	_seatClass = seatClass;
	_status = status;
	_seatPrice = seatPrice;
	_phoneNumber ="";
}

// Getter
string Seat::getSeatID() {
	// A -> E, 1 -> 6
	return _seatID;
}
string Seat::getSeatClass() {
	// Vip , Normal , Couple
	return _seatClass;
}
char Seat::getStatus() {
	// A : Available , O : Orderded , P : Pending
	return _status;
}
float Seat::getSeatPrice() {
	// 1: Vip = 200 ; Normal = 100 ; Couple = 250
	return _seatPrice;
}
string Seat::getPhoneNumber() {
	return _phoneNumber;
}

// Setter
void Seat::setSeatID(string seatID) {
	this->_seatID = seatID;
}
void Seat::setSeatClass(string seatClass) {
	this->_seatClass = seatClass;
}
void Seat::setStatus(char status) {
	this->_status = status;
}
void Seat::setSeatPrice(float seatPrice) {
	this->_seatPrice = seatPrice;
}
void Seat::setPhoneNumber(string phoneNumber) {
	this->_phoneNumber = phoneNumber;
}