#include "console_io.h"

#include "data_manip.h"
#include "file_io.h"

#include <cmath>
#include <iomanip>
#include <sstream>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

void clearConsole()
{
#ifdef _WIN32
	// Thank you, Microsoft <3
	// https://docs.microsoft.com/en-us/windows/console/clearing-the-screen

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	SMALL_RECT scrollRect;
	COORD scrollTarget;
	CHAR_INFO fill;
	HANDLE hConsole;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (hConsole == INVALID_HANDLE_VALUE) {
		return;
	}

	// Get the number of character cells in the current buffer.
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
		return;
	}

	// Scroll the rectangle of the entire buffer.
	scrollRect.Left = 0;
	scrollRect.Top = 0;
	scrollRect.Right = csbi.dwSize.X;
	scrollRect.Bottom = csbi.dwSize.Y;

	// Scroll it upwards off the top of the buffer with a magnitude of the entire height.
	scrollTarget.X = 0;
	scrollTarget.Y = (SHORT)(0 - csbi.dwSize.Y);

	// Fill with empty spaces with the buffer's default text attribute.
	fill.Char.UnicodeChar = TEXT(' ');
	fill.Attributes = csbi.wAttributes;

	// Do the scroll
	ScrollConsoleScreenBuffer(hConsole, &scrollRect, NULL, scrollTarget, &fill);

	// Move the cursor to the top left corner too.
	csbi.dwCursorPosition.X = 0;
	csbi.dwCursorPosition.Y = 0;

	SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
#endif
}

void printNewlines(size_t n)
{
	for (size_t i = 0; i < n; i++) {
		cout << endl;
	}
}

void displayMenuOptions(const vector<const char *> &options)
{
	for (size_t i = 0; i < options.size(); i++) {
		cout << i + 1 << ". " << options[i] << endl;
	}
}

void getMenuChoice(size_t &choice, size_t maxValue, size_t minValue)
{
	while (true) {
		try {
			cout << "Enter choice (" << minValue << " - " << maxValue << "): ";
			getUnsignedNumber(cin, choice, '\n', maxValue, minValue);
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
	vector<const char *> options = {"List schools",
									"Select school",
									"Add school",
									"Remove school",
									"Restore from backup",
									"Store to backup",
									"Quit"};

	displayMenuOptions(options);
	getMenuChoice(choice, options.size());

	clearConsole();

	switch (choice) {
		case 1:
			listTable(schools);
			break;
		case 2:
			menuSelect(schools);
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

	printNewlines(1);

	return true;
}

void menuSelect(vector<SCHOOL> &schools)
{
	size_t choice;

	clearConsole();

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
		clearConsole();

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
	clearConsole();

	if (choice[0] != 'y' and choice[0] != 'Y') return;

	storeSchools(schools, "backup");
}

bool menu(SCHOOL &school)
{
	size_t choice;
	vector<const char *> options = {"Edit name", "Edit city", "Edit address",
									"List students", "Select student",
									"List teachers", "Select teacher",
									"List teams", "Select team",
									"List projects", "Select project",
									"Back to schools"};

	displayMenuOptions(options);
	getMenuChoice(choice, options.size());

	clearConsole();

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
			listTable(school.students, school);
			break;
		case 5:
			menuSelect(school.students, school);
			break;
		case 6:
			listTable(school.teachers, school);
			break;
		case 7:
			menuSelect(school.teachers, school);
			break;
		case 8:
			listTable(school.teams, school);
			break;
		case 9:
			menuSelect(school.teams, school);
			break;
		case 10:
			listTable(school.projects, school);
			break;
		case 11:
			menuSelect(school.projects, school);
			break;
		case 12:
			return false;
	}

	printNewlines(1);

	return true;
}

void menuEditCity(SCHOOL &school)
{
	cout << "Current city: " << school.city << endl;
	cout << "Enter new school city: ";
	getline(cin, school.city);

	clearConsole();
}

void menuEditAddress(SCHOOL &school)
{
	cout << "Current address: " << school.address << endl;
	cout << "Enter new school address: ";
	getline(cin, school.address);

	clearConsole();
}

bool menu(STUDENT &student, const SCHOOL &parentSchool)
{
	size_t choice;
	vector<const char *> options = {"Edit first name",
									"Edit last name",
									"Edit email",
									"Edit class",
									"Back to school"};

	displayMenuOptions(options);
	getMenuChoice(choice, options.size());

	clearConsole();

	switch (choice) {
		case 1:
			menuEditFirstName(student);
			break;
		case 2:
			menuEditLastName(student);
			break;
		case 3:
			menuEditEmail(student);
			break;
		case 4:
			menuEditClass(student);
			break;
		case 5:
			return false;
	}

	printNewlines(1);

	return true;
}

void menuEditClass(STUDENT &student)
{
	cout << "Current class: " << student.grade << ' ' << student.classLetter << endl;
	cout << "Enter new class: ";

	if (!getStudentClass(student.grade, student.classLetter)) {
		cout << "Invalid input!" << endl;
		return;
	}

	clearConsole();
}

bool getStudentClass(unsigned &grade, char &classLetter)
{
	string stemp;
	unsigned utemp;
	char ctemp;

	getline(cin, stemp);

	stringstream line(stemp);
	line.exceptions(ios::failbit | ios::badbit);

	try {
		getUnsignedNumber(line, utemp, ' ', 12, 1);
		if (line.str().empty()) return false;
		getline(line, stemp);
		ctemp = stemp[0];
	}
	catch (...) {
		return false;
	}

	grade = utemp;
	classLetter = ctemp;

	return true;
}

bool menu(TEACHER &teacher, const SCHOOL &parentSchool)
{
	size_t choice;
	vector<const char *> options = {"Edit first name",
									"Edit last name",
									"Edit email",
									"List teams",
									"Assign team",
									"Dismiss team",
									"Back to school"};

	displayMenuOptions(options);
	getMenuChoice(choice, options.size());

	clearConsole();

	switch (choice) {
		case 1:
			menuEditFirstName(teacher);
			break;
		case 2:
			menuEditLastName(teacher);
			break;
		case 3:
			menuEditEmail(teacher);
			break;
		case 4:
			listTable(teacher.teams, parentSchool.teams, parentSchool);
			break;
		case 5:

			break;
		case 6:
			break;
		case 7:
			return false;
	}

	printNewlines(1);

	return true;
}

void menuEditProject(TEAM &team)
{
	cout << "Current project: " << team.project << endl;
	cout << "Enter new project: ";
	getline(cin, team.project);

	clearConsole();
}

bool menu(TEAM &team, const SCHOOL &parentSchool)
{
	size_t choice;
	vector<const char *> options = {"Edit name",
									"Edit description",
									"Edit status",
									"Change project",
									"List members",
									"Select member",
									"Add member",
									"Delete member",
									"Back to school"};

	displayMenuOptions(options);
	getMenuChoice(choice, options.size());

	clearConsole();

	switch (choice) {
		case 1:
			menuEditName(team);
			break;
		case 2:
			menuEditDescription(team);
			break;
		case 3:
			menuEditStatus(team);
			break;
		case 4:
			break;
		case 5:
			listTable(team.members, parentSchool);
			break;
		case 6:
			menuSelect(team.members, parentSchool);
			break;
		case 7:
			break;
		case 8:
			break;
		case 9:
			return false;
	}

	printNewlines(1);

	return true;
}

bool menu(PROJECT &project, const SCHOOL &parentSchool)
{
	size_t choice;
	vector<const char *> options = {"Edit name",
									"Edit description",
									"Edit status",
									"List teams",
									"Assign team",
									"Dismiss team",
									"Back to school"};

	displayMenuOptions(options);
	getMenuChoice(choice, options.size());

	clearConsole();

	switch (choice) {
		case 1:
			menuEditName(project);
			break;
		case 2:
			menuEditDescription(project);
			break;
		case 3:
			menuEditStatus(project);
			break;
		case 4:
			listTable(project.teams, parentSchool.teams, parentSchool);
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			return false;
	}

	printNewlines(1);

	return true;
}

bool menu(TEAM_MEMBER &member, const SCHOOL &parentSchool)
{
	size_t choice;
	vector<const char *> options = {"Edit role",
									"Back to team"};

	displayMenuOptions(options);
	getMenuChoice(choice, options.size());

	clearConsole();

	switch (choice) {
		case 1:
			menuEditRole(member);
			break;
		case 2:
			return false;
	}

	printNewlines(1);

	return true;
}

void menuEditRole(TEAM_MEMBER &member)
{
	cout << "Legend:" << endl;
	for (int i = 0; i <= 3; i++) {
		cout << '(' << i << ") " << toString((TEAM_MEMBER::ROLE)i) << endl;
	}
	cout << endl;

	cout << "Current role: " << (unsigned)member.role << endl;
	cout << "Enter new role: ";

	try {
		getUnsignedNumber(cin, member.role, '\n', 3);
	}
	catch (...) {
		cout << "Invalid input!" << endl;
		return;
	}

	clearConsole();
}
