#include "console_io.h"

#include "data_manip.h"
#include "file_io.h"

#include <cmath>
#include <iomanip>
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
			selectSchool(schools);
			break;
		case 2:
			listSchools(schools);
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

void selectSchool(vector<SCHOOL> &schools)
{
	size_t choice;

	if (schools.empty()) {
		cout << "There are currently no schools." << endl;
		return;
	}

	listSchools(schools);

	getMenuChoice(choice, schools.size());

	menuDriverSchool(dereferenceElement(schools, schools.begin() + (choice - 1)));
}

void listSchools(const vector<SCHOOL> &schools)
{
	ios initialState(nullptr);

	size_t colNoWidth, colNameWidth, colCityWidth, colAddressWidth, colStudentsWidth, colTeachersWidth, colTeamsWidth, colProjectsWidth;
	SCHOOL currSchool;
	string labelNo, labelName, labelCity, labelAddress, labelStudents, labelTeachers, labelTeams, labelProjects;

	if (schools.empty()) {
		cout << "There are currently no schools." << endl;
		return;
	}

	initialState.copyfmt(cout);

	labelNo = "No.";
	labelName = "Name";
	labelCity = "City";
	labelAddress = "Address";
	labelStudents = "Students";
	labelTeachers = "Teachers";
	labelTeams = "Teams";
	labelProjects = "Projects";

	colNoWidth = max((size_t)ceil(log10(schools.size())), labelNo.size()) + 1;
	colNameWidth = labelName.size();
	colCityWidth = labelCity.size();
	colAddressWidth = labelAddress.size();
	colStudentsWidth = labelStudents.size() + 1;
	colTeachersWidth = labelTeachers.size() + 1;
	colTeamsWidth = labelTeams.size() + 1;
	colProjectsWidth = labelProjects.size() + 1;

	for (auto it = schools.begin(); it != schools.end(); it++) {
		currSchool = dereferenceElement(schools, it);

		colNameWidth = max(colNameWidth, currSchool.name.size());
		colCityWidth = max(colCityWidth, currSchool.city.size());
		colAddressWidth = max(colAddressWidth, currSchool.address.size());
	}

	colNameWidth++;
	colCityWidth++;
	colAddressWidth++;

	cout << left << setw(colNoWidth) << labelNo
		 << setw(colNameWidth) << labelName
		 << setw(colCityWidth) << labelCity
		 << setw(colAddressWidth) << labelAddress
		 << setw(colStudentsWidth) << labelStudents
		 << setw(colTeachersWidth) << labelTeachers
		 << setw(colTeamsWidth) << labelTeams
		 << setw(colProjectsWidth) << labelProjects << endl;

	cout << string(colNoWidth + colNameWidth + colCityWidth + colAddressWidth + colStudentsWidth + colTeachersWidth + colTeamsWidth + colProjectsWidth, '-') << endl;

	for (size_t i = 0; i < schools.size(); i++) {
		cout << left << setw(colNoWidth) << i + 1
			 << setw(colNameWidth) << schools[i].name
			 << setw(colCityWidth) << schools[i].city
			 << setw(colAddressWidth) << schools[i].address
			 << setw(colStudentsWidth) << schools[i].students.size()
			 << setw(colTeachersWidth) << schools[i].teachers.size()
			 << setw(colTeamsWidth) << schools[i].teams.size()
			 << setw(colProjectsWidth) << schools[i].projects.size() << endl;
	}

	cout.copyfmt(initialState);
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

void menuDriverSchool(SCHOOL &school)
{
	while (menuSchool(school)) {};
}

bool menuSchool(SCHOOL &school)
{
	size_t choice;
	vector<const char *> options = {"Edit name", "Edit city", "Edit address",
									"Select student", "List students",
									"Select teacher", "List teacher",
									"Select team", "List team",
									"Select project", "List project",
									"Back to schools"};

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
