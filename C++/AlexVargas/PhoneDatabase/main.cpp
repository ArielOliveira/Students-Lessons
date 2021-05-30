#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <cctype>
#include "phone_db.h"
#include "phone_db.cpp"

using std::vector;
using std::string;
using std::map;
using std::cout;
using std::cin;
using std::endl;

int main() {

cout << "Info: Welcome to the Phone Database!" << endl;
cout << "Info: Please enter a command" << endl;

string command;
Database p;
while(cin >> command) {


if (command == "C") {
	string firstName;
	string lastName;
	cin >> lastName;
	cin >> firstName;

	Contact cname(lastName, firstName);
	

		if((p.findByName(lastName, firstName)).ifMatch("NULL", "NULL")) {

			p.addContact(cname);
			cout << "Result: Contact Created" << endl;
	
	}

		else {

			cout << "Error: Contact already exists" << endl;
	
	}
}

if (command == "D") {
//input function that deletes the contact
	string lastName;
	string firstName;
	cin >> lastName;
	cin >> firstName;

	Contact cname(lastName, firstName);

	if (p.deleteContact(cname)) {
		//p.deleteContact(cname);

		cout << "Error: Contact not Found" << endl;
	}

	else {
		cout << "Result: Contact Deleted" << endl;
	}

}

if (command == "N"){
	string lastName;
	string firstName;
	string phoneType;
	string phoneNumber;
	cin >> lastName;
	cin >> firstName;
	cin >> phoneType;
	cin >> phoneNumber;
	Contact cname = ((p.findByName(lastName, firstName)));

	//Contact cname(lastName, firstName);
	

		if((cname.ifMatch("NULL", "NULL"))) {

			cout << "Error: Contact not Found" << endl;
		
		}
	

		else if (phoneType != "CELL" && phoneType != "HOME" && phoneType != "WORK" && phoneType != "FAX" && phoneType != "VOIP") {
			cout << "Error: Invalid phone number type" << endl;
		}



		else if (phoneNumber.length()!= 12) {

		cout << "Error: Not a valid phone number" << endl;
	}

		else{
		// need to add contact to name
		cname.addNumber(phoneType, phoneNumber);
		//make helper function updateVec(cname, lastName, firstName)
		for(int i=0; i < p.data.size(); i++) {
			Contact temp = p.data[i];
			if (temp.ifMatch(lastName, firstName)) {
				p.data[i] = cname;

			}
			
		}
	// iterate through vector to find match in the vector, then update contact
		cout << "Result: Successfully Added Number" << endl;
		cout << cname.cell << endl;
		cout << cname.work << endl;
	}
}

if (command == "X") {
	string lastName;
	string firstName;
	string phoneType;
	cin >> lastName;
	cin >> firstName;
	cin >> phoneType;


	if((p.findByName(lastName, firstName)).ifMatch("NULL", "NULL")) {

			cout << "Error: Contact not Found" << endl;
	}
	else {
		
		//need to access the element from N, edit the phoneType field, then update the vector with the new element.
		p.findByName(lastName,firstName).deleteNumber(phoneType);
		cout << "Result: Phone Number Deleted" << endl;
		cout << cname.cell << endl;
	}

}

if (command == "P") {
string lastName;
string firstName;
//((p.findByName(lastName, firstName)).ifMatch(lastName, firstName))
cin >> lastName;
cin >> firstName;
//cout << p.findByName(lastName, firstName) << endl;
Contact cname(lastName, firstName);
cout << cname.cell << endl;
//cname.printNumbers();

}


//}

if (command == "L") {
		//edit to make them print in alphabetical order
	p.listContacts();

	}

if (command == "S") {
	std::ofstream file;
	file.open("output.txt");
	//for (Contact i : p) {
		for(int i=0; i < p.data.size(); i++) {
		//file << p.data[i] << endl;
	}

}

if (command == "Q")
	break;
	
	}
	cout << "Info: Thank you for using the Phone Database!" << endl;
	return 0;
}



