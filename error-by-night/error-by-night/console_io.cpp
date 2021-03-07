#include "console_io.h"

#include "data_manip.h"
#include "file_io.h"

#include <cmath>
#include <iomanip>

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

bool menu(vector<SCHOOL> &schools)
{
	size_t choice;
	vector<const char *> options = {"Select school", "List schools", "Add school", "Remove school", "Restore from backup", "Store to backup", "Quit"};

	displayMenuOptions(options);
	getMenuChoice(choice, options.size());

	switch (choice) {
		case 1:
			menuSelect(schools);
			break;
		case 2:
			listTable(schools);
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

void menuSelect(vector<SCHOOL> &schools)
{
	size_t choice;

	if (schools.empty()) {
		std::cout << "There is currently nothing to select." << std::endl;
		return;
	}

	listTable(schools);

	getMenuChoice(choice, schools.size());

	menuDriver(dereferenceElement(schools, schools.begin() + (choice - 1)));
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

bool menu(SCHOOL &school)
{
	size_t choice;
	vector<const char *> options = {"Edit name", "Edit city", "Edit address",
									"Select student", "List students",
									"Select teacher", "List teachers",
									"Select team", "List teams",
									"Select project", "List projects",
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
			menuSelect(school.students, school);
			break;
		case 5:
			listTable(school.students, school);
			break;
		case 6:
			menuSelect(school.teachers, school);
			break;
		case 7:
			listTable(school.teachers, school);
			break;
		case 8:
			menuSelect(school.teams, school);
			break;
		case 9:
			listTable(school.teams, school);
			break;
		case 10:
			menuSelect(school.projects, school);
			break;
		case 11:
			listTable(school.projects, school);
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

bool menu(STUDENT &student, const SCHOOL &parentSchool)
{
	return true;
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

bool menu(TEACHER &teacher, const SCHOOL &parentSchool)
{
	return true;
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

void menuEditName(TEAM &team)
{
	cout << "Current name: " << team.name << endl;
	cout << "Enter new name: ";
	getline(cin, team.name);
}

void menuEditDescription(TEAM &team)
{
	cout << "Current description: " << team.description << endl;
	cout << "Enter new description: ";
	getline(cin, team.description);
}

void menuEditProject(TEAM &team)
{
	cout << "Current project: " << team.project << endl;
	cout << "Enter new project: ";
	getline(cin, team.project);
}

void menuEditStatus(TEAM &team)
{
	cout << "Current status: " << (unsigned)team.status << endl;
	cout << "Enter new project: ";
	getUnsignedNumber(cin, team.status, '\n', 1);
}

bool menu(TEAM &team, const SCHOOL &parentSchool)
{
	return true;
}

bool menu(PROJECT &project, const SCHOOL &parentSchool)
{
	return true;
}

bool menu(TEAM_MEMBER &members, const SCHOOL &parentSchool)
{
	return true;
}
