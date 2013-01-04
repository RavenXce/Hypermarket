#include "stdafx.h"
#include "date.h"
using namespace std;
Date::Date() { 
	struct tm *ts;
	time_t t = time(NULL);
	ts = localtime (&t);
	year = ts->tm_year+1900;
	month = ts->tm_mon+1;
	day = ts->tm_mday;
}

Date::Date(int raw){
		day = raw/1000000;
		raw %= 1000000;
		month = raw/10000;
		raw %= 10000;
		year = raw;
}

Date::Date(int yy, int mm, int dd) : year(yy), month(mm), day(dd)   { }

//deprecated
long Date::operator-(const Date &other) const { return getJulianDay()-other.getJulianDay(); }

string Date::formatted() const {
	ostringstream ret;
	ret << day << "/" << month << "/" << year;
	return ret.str();
}

long Date::getJulianDay() const {
	int a = (14-month)/12;
	int y = (year + 4800 - a);
	int m = month + (12*a) - 3;
	return day + ((153*m)+2)/5 + 365*y + y/4 - y/100 + y/400 - 32045;
	// source for coversion algorithm: wikipedia
}