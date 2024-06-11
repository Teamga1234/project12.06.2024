#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "Date.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <clocale>
#include <ctime>
#include <stdlib.h>
#include "counter_of_rent_days.h"

using namespace std;

struct disc_rental {
	char temp_owner[100] = "";
	char address[50] = "";
	char phone_temp_owner[20] = "";
	Date date_from;
	Date date_to;
	unsigned short price_rental = 0;
	void fill_rental_form()
	{
		cout << "Input date from(dd mm yyyy): ";
		cin >> date_from.day >> date_from.month >> date_from.year;
		cout << "Input date to(dd mm yyyy): ";
		cin >> date_to.day >> date_to.month >> date_to.year;
		cin.ignore();
		cout << "Input your full name: ";
		cin.getline(temp_owner, 100);
		
		cout << "Input your address: ";
		cin.getline(address, 50);
		
		cout << "Input your phone number: ";
		cin.getline(phone_temp_owner, 50);
		price_rental = daysBetweenDates(date_from, date_to);
		// 1 день аренди  == 1 $
	}
	void show_disc_rental()
	{

		cout << "\tTemp_owner: " << temp_owner << endl;
		cout << "\tAddress: " << address << endl;
		cout << "\tPhone: " << phone_temp_owner << endl;
		cout << "\tDate_from: " << date_from.toString("%Y %m %d") << endl;
		cout << "\tDate_to: " << date_to.toString("%Y %m %d") << endl;
		cout << "\tPrice_rental: " << price_rental << "$\n\n";
		
	}
};
struct owner_disk {
	char owner_forever[100] = "";
	Date day_when_sold;

	void fill_owner_form()
	{
		cout << "Enter the date the disc was sold (dd mm yyyy): ";
		cin >> day_when_sold.day >> day_when_sold.month >> day_when_sold.year;
		cin.ignore();
		
		cout << "Input your full name: ";
		cin.getline(owner_forever, 100);
		
	}
	void show_disc_owner()
	{

		cout << "\tOwner: " << owner_forever << endl;
		cout << "\tThe date when the disc was sold: "<< day_when_sold.toString("%Y %m %d") << endl << endl;

	}
};