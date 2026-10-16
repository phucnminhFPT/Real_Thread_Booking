#ifndef INPUTHELPER_H
#define INPUTHELPER_H

#include <string>

using namespace std;

int readInt(string message, int minValue, int maxValue);

float readPositiveMoney(string message);

string readPhoneNumber();

string readCustomerName();

string readSeatID();

#endif