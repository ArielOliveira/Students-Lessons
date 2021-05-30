#ifndef PHONE_DB_H
#define PHONE_DB_H
#include <vector>
#include <string>

using std::vector;
using std::string;
using std::cout;
using std::endl;

class Contact {
	public:
		string firstName;
		string lastName;
		string home;
		string cell;
		string work;
		string fax;
		string voip;
	public:
		Contact(string lName, string fName) { lastName = lName; firstName = fName; } //constructor uses string of first and last name
		void printNumbers() {
		cout << cell << endl;
		cout << fax << endl;
		cout << home << endl;
		cout << voip << endl;
		cout << work << endl;

		}; // prints all strings that are not null for a specific contact (not including firstName and lastName)

		void addNumber(string phoneType, string phoneNumber);

		bool ifMatch(string lName, string fName) { if (lName == lastName && fName == firstName) { return true; } };

		void printName() { cout << lastName + ", " + firstName << endl; };

		void changeNumber(string type, string number) {}; //using type, change number using switch case

		void deleteNumber (string type); //command X; make string of type specified to null (using switch case)
		
};

class Database {
	public: // change back to private
		vector<Contact> data;

	//public:
		Database() { };

		void addContact(Contact name) { data.push_back(name); };



		int deleteContact(Contact name);

		void listContacts(); //for loop iterate through data and print each last, then first

		Contact& findByName(string fName, string lName); //use string of first and last name and find using a for loop

		void printNumbers(string fName, string lName) {}; //use findByName to find the contact, then using the contact you compare to vector using a for loop. once found, use printNumbers in contact class


		void saveToFile() {}; //save to a file (print new line for every contact and list each phone number)

		void readFromFile() {}; //read from the saved file to the database
};
#endif

