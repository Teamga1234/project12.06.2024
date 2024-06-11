#pragma once
#include "structs_of_info_disk.h"
#include "Functions.h"
using namespace std;

struct song {
	short type_song = 0; //0 - free, 1 - rent, 2 - sold
	unsigned int number_song = 0;
	char song_title[25] = "";
	char author_name[50] = "";
	unsigned short year_of_create = 2024;
	unsigned short price_of_song = 0;
	disc_rental person_r = { "1", "1", "1", {0, 0, 0}, {0, 0, 0}, 0 };
	owner_disk person_o = { "1", {0, 0, 0} };
	void fill_song_form()
	{
		cout << "Enter song title: ";
		cin.getline(song_title, 25);
		cout << "Enter author_name: ";
		cin.getline(author_name, 50);
		cout << "Enter year of song: ";
		cin >> year_of_create;
		cout << "Enter price of song: ";
		cin >> price_of_song;
	}
	void show_song_admin()
	{
		cout << "-----------------------------------------------------\n";
		cout << "\n\tNumber: " << number_song << endl;
		cout << "\tName: " << song_title << endl;
		cout << "\tAuthor: " << author_name << endl;
		cout << "\tYear: " << year_of_create << endl;
		cout << "\tPrice: " << price_of_song << "$\n";
		if (type_song == 1)
		{
			cout << "\tTemp_owner: " << person_r.temp_owner << endl;
			cout << "\tAddress: " << person_r.address << endl;
			cout << "\tDate_from: " << person_r.date_from.toString("%Y %m %d") << endl;
			cout << "\tDate_to: " << person_r.date_to.toString("%Y %m %d") << endl;
			cout << "\tPrice_rental: " << person_r.price_rental << "$\n\n";
			cout << "-----------------------------------------------------\n";
		}
		else if (type_song == 2)
		{
			cout << "\tOwner: " << person_o.owner_forever << endl;
			cout << "\tThe date when the disc was sold: " << person_o.day_when_sold.toString("%Y %m %d") << endl << endl;
			cout << "-----------------------------------------------------\n";
		}
		else
		{
			cout << "\tSong doesn`t have the owner\n";
			cout << "-----------------------------------------------------\n";
		}
	}
	void show_song_buy()
	{
		cout << "-----------------------------------------------------\n";
		cout << "\n\tNumber: " << number_song << endl;
		cout << "\tName: " << song_title << endl;
		cout << "\tAuthor: " << author_name << endl;
		cout << "\tYear: " << year_of_create << endl;
		cout << "\tPrice: " << price_of_song << "$\n";
		if (type_song == 0)
		{
			cout << "\tSong doesn`t have the owner\n" << endl << endl;
			cout << "-----------------------------------------------------\n";
		}
		else
		{
			cout << "\tSong have the owner\n";
			cout << "-----------------------------------------------------\n";
		}
	}
};