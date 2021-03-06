#include "console_io.h"

#include "file_io.h"

#include <iostream>

using namespace std;

void displayMenuOptions(const vector<const char *> &options)
{
	for (size_t i = 0; i < options.size(); i++) {
		cout << i + 1 << ". " << options[i] << endl;
	}
}

void getMenuChoice(size_t &choice, size_t optionCount)
{
	while (true) {
		try {
			cout << "Enter choice (1 - " << optionCount << "): ";
			getUnsignedNumber(cin, choice, '\n', optionCount);
		}
		catch (...) {
			cout << "Invalid input!" << endl;
			continue;
		}
		break;
	}
}

void menuDriverMain(vector<SCHOOL> &schools)
{
	while (menuMain(schools)) {};
}

bool menuMain(vector<SCHOOL> &schools)
{
	size_t choice;
	vector<const char *> options = {"Select school", "List schools", "Add school", "Remove school", "Restore from backup", "Store to backup", "Quit"};

	displayMenuOptions(options);
	getMenuChoice(choice, options.size());

	switch (choice) {
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			menuRestore(schools);
			break;
		case 6:
			menuStore(schools);
			break;
		case 7:
			return false;
	}

	return true;
}

void menuRestore(vector<SCHOOL> &schools)
{
	string choice;

	if (!schools.empty()) {
		cout << "WARNING: This operation will override your existing schools and you will not be able to recover them." << endl
			 << "Do you wish to proceed? (y/n): ";

		getline(cin, choice);

		if (choice[0] != 'y' and choice[0] != 'Y') return;
	}

	restoreSchools(schools, "backup");
}

void menuStore(const vector<SCHOOL> &schools)
{
	string choice;

	cout << "WARNING: This operation will override your existing backup and you will no longer be able to access it." << endl
		 << "Do you wish to proceed? (y/n): ";

	getline(cin, choice);

	if (choice[0] != 'y' and choice[0] != 'Y') return;

	storeSchools(schools, "backup");
}

bool menuSchool(SCHOOL &school)
{
	size_t choice;
	vector<const char *> options = {"Edit name", "Edit city", "Edit address",
									"Select student", "List students",
									"Select teacher", "List teacher",
									"Select team", "List team",
									"Select project", "List project",
									"Quit"};

	displayMenuOptions(options);
	getMenuChoice(choice, options.size());

	switch (choice) {
		case 1:
			menuEditName(school);
			break;
		case 2:
			menuEditCity(school);
			break;
		case 3:
			menuEditAddress(school);
			break;
		case 4:

			break;
		case 5:

			break;
		case 6:

			break;
		case 7:

			break;
		case 8:

			break;
		case 9:

			break;
		case 10:

			break;
		case 11:

			break;

		case 12:
			return false;
	}

	return true;
}

void menuEditName(SCHOOL &school)
{
	cout << "Current name: " << school.name << endl;
	cout << "Enter new school name: ";
	getline(cin, school.name);
}

void menuEditCity(SCHOOL &school)
{
	cout << "Current city: " << school.city << endl;
	cout << "Enter new school city: ";
	getline(cin, school.city);
}

void menuEditAddress(SCHOOL &school)
{
	cout << "Current address: " << school.address << endl;
	cout << "Enter new school address: ";
	getline(cin, school.address);
}

void menuEditFirstName(STUDENT &student)
{
	cout << "Current first name: " << student.firstName << endl;
	cout << "Enter new first name: ";
	getline(cin, student.firstName);
}

void menuEditLastName(STUDENT &student)
{
	cout << "Current last name: " << student.lastName << endl;
	cout << "Enter new last name: ";
	getline(cin, student.lastName);
}

void menuEditEmail(STUDENT &student)
{
	cout << "Current email: " << student.email << endl;
	cout << "Enter new email: ";
	getline(cin, student.email);
}

void menuEditFirstName(TEACHER &teacher)
{
	cout << "Current first name: " << teacher.firstName << endl;
	cout << "Enter new first name: ";
	getline(cin, teacher.firstName);
}

void menuEditLastName(TEACHER &teacher)
{
	cout << "Current last name: " << teacher.lastName << endl;
	cout << "Enter new last name: ";
	getline(cin, teacher.lastName);
}

void menuEditEmail(TEACHER &teacher)
{
	cout << "Current email: " << teacher.email << endl;
	cout << "Enter new email: ";
	getline(cin, teacher.email);
}
