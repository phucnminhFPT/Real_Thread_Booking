#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "CustomerManagement.h"
#include "SeatManagement.h"
#include <string>

using namespace std;

class FileManager
{
private:
	string _fileName;

public:
	FileManager(string fileName = "BookingData.txt");

	void save(CustomerManagement &customerManagement,
			  SeatManagement &seatManagement);

	void load(CustomerManagement &customerManagement,
			  SeatManagement &seatManagement);
};

#endif