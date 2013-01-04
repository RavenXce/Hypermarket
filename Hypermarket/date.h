#ifndef DATE_H
#define DATE_H

#include <ctime>
#include <string>
#include <sstream>

using namespace std;
public  class Date {
private:
	int year, month, day;
public:
	Date(); 
	Date(int);
	Date(int year, int month, int day);
	string formatted() const;
	int getYear() const { return year; }
	int getMonth() const { return month; }
	int getDay() const { return day; }
	long getJulianDay() const;
	long operator-(const Date &) const;
};

#endif DATE_H