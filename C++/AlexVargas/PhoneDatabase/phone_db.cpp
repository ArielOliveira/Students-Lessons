#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <cctype>
#include "phone_db.h"

using std::vector;
using std::string;
using std::map;
using std::cout;
using std::cin;
using std::endl;



/* for loop iterate through data and print each last, then first
 *
 */
void Database::listContacts() {
	for(vector<Contact>::iterator it = data.begin(); it != data.end(); it++) {
	  Contact temp = *it;
		temp.printName();
	}
};

Contact Database::findByName(string lName, string fName) {
	for(vector<Contact>::iterator it = data.begin(); it != data.end(); it++) {
	  //Contact temp = *it;
		if ((*it).ifMatch(lName, fName)) {
			return *it;
		}
	}
	Contact z("NULL", "NULL");
	return z;
}
int Database::deleteContact(Contact name) {
	for(vector<Contact>::iterator it = data.begin(); it != data.end(); it++) {
	  //Contact temp = *it;
		if ((*it).ifMatch(name.lastName, name.firstName)) {
			data.erase(it);
			return 0;
		}
		
	}
			return 1;
}




void Contact::addNumber(string phoneType, string phoneNumber) {

/*
		for(vector<Contact>::iterator it = data.begin(); it != data.end(); it++) {
	  //Contact temp = *it;
		if ((*it).ifMatch(lName, fName)) {
			break;
		}
	findByName()

			if (phoneType == "CELL") {
				it->cell = phoneNumber;
				cell = phoneNumber;
			}
			if (phoneType == "HOME") {
				it->home = phoneNumber;
			}
			if (phoneType == "WORK") {
				it->work = phoneNumber;
			}
			if (phoneType == "FAX") {
				it->fax = phoneNumber;
			}
			if (phoneType == "VOIP") {
				it->voip = phoneNumber;
			}
		*/
			if (phoneType == "CELL") {
				cell = phoneNumber;
			}
			if (phoneType == "HOME") {
				home = phoneNumber;
			}
			if (phoneType == "WORK") {
				work = phoneNumber;
			}
			if (phoneType == "FAX") {
				fax = phoneNumber;
			}
			if (phoneType == "VOIP") {
				voip = phoneNumber;
			}

		}


void Contact::deleteNumber (string phoneType) {
			if (phoneType == "CELL") {
				cell = "";
			}
			if (phoneType == "HOME") {
				home = "";
			}
			if (phoneType == "WORK") {
				work = "";
			}
			if (phoneType == "FAX") {
				fax = "";
			}
			if (phoneType == "VOIP") {
				voip = "";
			}	

}


