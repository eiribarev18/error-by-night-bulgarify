#include "console_io.h"

#include "data_manip.h"
#include "file_io.h"

#include <cmath>
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace std;

void printNewlines(size_t n)
{
	for (size_t i = 0; i < n; i++) {
		cout << endl;
	}
}

bool getKey(size_t &key)
{
	try {
		getUnsignedNumber(cin, key);
	}
	catch (...) {
		return false;
	}

	return true;
}

bool getKey(string &key)
{
	getline(cin, key);

	return true;
}

void displayMenuOptions(const vector<const char *> &options)
{
	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN);

	for (size_t i = 0; i < options.size(); i++) {
		cout << i + 1 << ". " << options[i] << endl;
	}

	cout << getAnsiEscape(ANSI_ESCAPE::RESET);
}

void getMenuChoice(size_t &choice, size_t maxValue, size_t minValue)
{
	cout << getAnsiEscape(ANSI_ESCAPE::FG_YELLOW);

	while (true) {
		cout << "Enter choice (" << minValue << " - " << maxValue << "): " << getAnsiEscape(ANSI_ESCAPE::FG_B_YELLOW);
		try {
			getUnsignedNumber(cin, choice, '\n', maxValue, minValue);
		}
		catch (...) {
			cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "Invalid input!" << getAnsiEscape(ANSI_ESCAPE::FG_YELLOW) << endl;
			continue;
		}
		break;
	}

	cout << getAnsiEscape(ANSI_ESCAPE::RESET);
}

bool menu(vector<SCHOOL> &schools)
{
	size_t choice;
	vector<const char *> options = {"Select school",
									"List schools",
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
			menuSelect(schools);
			break;
		case 2:
			listTable(schools);
			break;
		case 3:
			menuAdd(schools);
			break;
		case 4:
			menuRemove(schools);
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

bool menu(SCHOOL &school)
{
	size_t choice;
	vector<const char *> options = {"Edit name", "Edit city", "Edit address",
									"Select student", "Select teacher", "Select team", "Select project",
									"List students", "List teachers", "List teams", "List projects",
									"Add student", "Add teacher", "Add team", "Add project",
									"Remove student", "Remove teacher", "Remove team", "Remove project",
									"Queries",
									"Back to schools"};

	displayDetails(school);
	printNewlines(1);

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
			menuSelect(school.students, school);
			break;
		case 5:
			menuSelect(school.teachers, school);
			break;
		case 6:
			menuSelect(school.teams, school);
			break;
		case 7:
			menuSelect(school.projects, school);
			break;
		case 8:
			listTable(school.students, school);
			break;
		case 9:
			listTable(school.teachers, school);
			break;
		case 10:
			listTable(school.teams, school);
			break;
		case 11:
			listTable(school.projects, school);
			break;
		case 12:
			menuAdd(school.students, school);
			break;
		case 13:
			menuAdd(school.teachers, school);
			break;
		case 14:
			menuAdd(school.teams, school);
			break;
		case 15:
			menuAdd(school.projects, school);
			break;
		case 16:
			menuRemove(school.students, school);
			break;
		case 17:
			menuRemove(school.teachers, school);
			break;
		case 18:
			menuRemove(school.teams, school);
			break;
		case 19:
			menuRemove(school.projects, school);
			break;
		case 20:
			while (menuQueries(school)) {};
			break;
		case 21:
			return false;
	}

	printNewlines(1);

	return true;
}

bool menu(STUDENT &student, const SCHOOL &parentSchool)
{
	size_t choice;
	vector<const char *> options = {"Edit first name",
									"Edit last name",
									"Edit email",
									"Edit class",
									"Back to school"};

	displayDetails(student);
	printNewlines(1);

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

	displayDetails(teacher);
	printNewlines(1);

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
			menuLink(teacher.teams, parentSchool.teams, parentSchool);
			break;
		case 6:
			menuUnlink(teacher.teams, parentSchool.teams, parentSchool);
			break;
		case 7:
			return false;
	}

	printNewlines(1);

	return true;
}

bool menu(TEAM &team, const SCHOOL &parentSchool)
{
	size_t choice;
	vector<const char *> options = {"Edit name",
									"Edit description",
									"Edit status",
									"Change project",
									"Select members",
									"List member",
									"Add member",
									"Delete member",
									"Back to school"};

	displayDetails(team, parentSchool);
	printNewlines(1);

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
			menuEditProject(team, parentSchool);
			break;
		case 5:
			menuSelect(team.members, parentSchool);
			break;
		case 6:
			listTable(team.members, parentSchool);
			break;
		case 7:
			menuAdd(team.members, parentSchool);
			break;
		case 8:
			menuRemove(team.members, parentSchool);
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

	displayDetails(project);
	printNewlines(1);

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
			menuLink(project.teams, parentSchool.teams, parentSchool);
			break;
		case 6:
			menuUnlink(project.teams, parentSchool.teams, parentSchool);
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
	vector<const char *> options = {"Change student",
									"Edit role",
									"Back to team"};

	displayDetails(member, parentSchool);
	printNewlines(1);

	displayMenuOptions(options);
	getMenuChoice(choice, options.size());

	clearConsole();

	switch (choice) {
		case 1:
			menuEditUsername(member, parentSchool);
			break;
		case 2:
			menuEditRole(member);
			break;
		case 3:
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
		std::cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "There is currently nothing to select." << std::endl;
		return;
	}

	listTable(schools);

	getMenuChoice(choice, schools.size());

	menuDriver(dereferenceElement(schools, schools.begin() + (choice - 1)));
}

void menuAdd(vector<SCHOOL> &schools)
{
	SCHOOL newSchool;

	menuAddAdditionalPrep(newSchool);

	if (!addElement(schools, newSchool)) {
		cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "Failed to create school: Name already exists!" << endl;
		return;
	}

	menuDriver(dereferenceElement(schools, schools.begin() + (schools.size() - 1)));
}

void menuRemove(vector<SCHOOL> &schools)
{
	size_t choice;

	if (schools.empty()) {
		std::cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "There are currently no schools." << std::endl;
		return;
	}

	listTable(schools);

	getMenuChoice(choice, schools.size());

	deleteElement(schools, choice - 1);

	clearConsole();
}

void menuRestore(vector<SCHOOL> &schools)
{
	string choice;

	if (!schools.empty()) {
		cout << getAnsiEscape(ANSI_ESCAPE::FG_B_YELLOW) << "WARNING: This operation will override your existing schools and you will not be able to recover them." << endl
			 << getAnsiEscape(ANSI_ESCAPE::FG_YELLOW) << "Do you wish to proceed? (y/n): " << getAnsiEscape(ANSI_ESCAPE::FG_B_YELLOW);

		getline(cin, choice);
		clearConsole();

		if (choice[0] != 'y' and choice[0] != 'Y') return;
	}

	restoreSchools(schools, "backup");
}

void menuStore(const vector<SCHOOL> &schools)
{
	string choice;

	cout << getAnsiEscape(ANSI_ESCAPE::FG_B_YELLOW) << "WARNING: This operation will override your existing backup and you will no longer be able to access it." << endl
		 << getAnsiEscape(ANSI_ESCAPE::FG_YELLOW) << "Do you wish to proceed? (y/n): " << getAnsiEscape(ANSI_ESCAPE::FG_B_YELLOW);

	getline(cin, choice);
	clearConsole();

	if (choice[0] != 'y' and choice[0] != 'Y') return;

	storeSchools(schools, "backup");
}

void menuAddAdditionalPrep(SCHOOL &school)
{
	addElement(school.students, string("INVALID"), {});
	addElement(school.teachers, string("INVALID"), {});
	addElement(school.teams, 0ull, {"", "", "", {}, STATUS::ARCHIVED, "INVALID"});
	addElement(school.projects, string("INVALID"), {"", "", {}, STATUS::ARCHIVED});
}

void menuAddAdditionalPrep(TEAM &team)
{
	team.project = "INVALID";

	char *tempBuffer = new char[sizeof("YYYY-MM-DD")];
	time_t currTime;
	tm tm_;

	time(&currTime);

	// MS localtime_s
	localtime_s(&tm_, &currTime);

	strftime(tempBuffer, sizeof("YYYY-MM-DD"), "%F", &tm_);

	team.setupDate = tempBuffer;

	delete[] tempBuffer;
}

void menuAddAdditionalPrep(TEAM_MEMBER &member)
{
	member.username = "INVALID";
}

void menuEditCity(SCHOOL &school)
{
	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Current city: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << school.city << endl;
	cout << getAnsiEscape(ANSI_ESCAPE::FG_YELLOW) << "Enter new school city: " << getAnsiEscape(ANSI_ESCAPE::FG_B_YELLOW);
	getline(cin, school.city);

	clearConsole();
}

void menuEditAddress(SCHOOL &school)
{
	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Current address: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << school.address << endl;
	cout << getAnsiEscape(ANSI_ESCAPE::FG_YELLOW) << "Enter new school address: " << getAnsiEscape(ANSI_ESCAPE::FG_B_YELLOW);
	getline(cin, school.address);

	clearConsole();
}

void menuEditClass(STUDENT &student)
{
	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Current class: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << student.grade << ' ' << student.classLetter << endl;
	cout << getAnsiEscape(ANSI_ESCAPE::FG_YELLOW) << "Enter new class: " << getAnsiEscape(ANSI_ESCAPE::FG_B_YELLOW);

	if (!getStudentClass(student.grade, student.classLetter)) {
		cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "Invalid input!" << endl;
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

void menuEditUsername(TEAM_MEMBER &member, const SCHOOL &parentSchool)
{
	vector<const string *> keys;

	size_t choice;

	if (parentSchool.students.empty()) {
		cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "No students!" << endl;
		return;
	}

	listTable(parentSchool.students, parentSchool);

	keys.reserve(parentSchool.students.size());
	for (auto it = parentSchool.students.begin(); it != parentSchool.students.end(); it++) {
		keys.push_back(&it->first);
	}

	getMenuChoice(choice, parentSchool.students.size());

	member.username = *keys[choice - 1];

	clearConsole();
}

void menuEditRole(TEAM_MEMBER &member)
{
	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Legend:" << endl;
	for (int i = 0; i <= 3; i++) {
		cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << '(' << i << ") " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << toString((TEAM_MEMBER::ROLE)i) << endl;
	}
	cout << endl;

	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Current role: " << (unsigned)member.role << endl;
	cout << getAnsiEscape(ANSI_ESCAPE::FG_YELLOW) << "Enter new role: " << getAnsiEscape(ANSI_ESCAPE::FG_B_YELLOW);

	try {
		getUnsignedNumber(cin, member.role, '\n', 3);
	}
	catch (...) {
		clearConsole();
		cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "Invalid input!" << endl;
		return;
	}

	clearConsole();
}

void menuEditProject(TEAM &team, const SCHOOL &parentSchool)
{
	vector<const string *> keys;

	size_t choice;

	if (parentSchool.projects.empty()) {
		cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "No projects!" << endl;
		return;
	}

	listTable(parentSchool.projects, parentSchool);

	keys.reserve(parentSchool.projects.size());
	for (auto it = parentSchool.projects.begin(); it != parentSchool.projects.end(); it++) {
		keys.push_back(&it->first);
	}

	getMenuChoice(choice, parentSchool.projects.size());

	team.project = *keys[choice - 1];

	clearConsole();
}

bool menuQueries(const SCHOOL &school)
{
	size_t choice;
	vector<const char *> options = {"Get teachers wihout teams",
									"Back to school"};

	printNewlines(1);

	displayMenuOptions(options);
	getMenuChoice(choice, options.size());

	clearConsole();

	switch (choice) {
		case 1:
			menuQueryTeachersWithoutTeam(school);
			break;
		case 2:
			return false;
	}

	return true;
}

void menuQueryTeachersWithoutTeam(const SCHOOL &school)
{
	vector<const string *> keys;
	size_t choice;

	if (school.projects.empty()) {
		cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "No projects!" << endl;
		return;
	}

	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Select project:" << endl;
	printNewlines(1);

	listTable(school.projects, school);

	keys.reserve(school.projects.size());
	for (auto it = school.projects.begin(); it != school.projects.end(); it++) {
		keys.push_back(&it->first);
	}

	getMenuChoice(choice, school.projects.size());

	clearConsole();
	listTable(school.getTeachersWithoutTeam(*keys[choice - 1]), school.teachers, school);
}

void displayDetails(const STUDENT &student)
{
	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "First name: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << student.firstName << endl
		 << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Last name: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << student.lastName << endl
		 << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Email: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << student.email << endl
		 << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Class: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << student.grade << ' ' << student.classLetter << endl;

	cout << getAnsiEscape(ANSI_ESCAPE::RESET);
}

void displayDetails(const TEACHER &teacher)
{
	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "First name: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << teacher.firstName << endl
		 << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Last name: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << teacher.lastName << endl
		 << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Email: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << teacher.email << endl
		 << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Number of assigned teams: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << teacher.teams.size() << endl;

	cout << getAnsiEscape(ANSI_ESCAPE::RESET);
}

void displayDetails(const TEAM_MEMBER &member, const SCHOOL &parentSchool)
{
	const STUDENT &student = dereferenceElement(parentSchool.students, member.username);

	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Student: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << student.firstName << ' ' << student.lastName << endl
		 << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Role: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << toString(member.role) << endl;

	cout << getAnsiEscape(ANSI_ESCAPE::RESET);
}

void displayDetails(const TEAM &team, const SCHOOL &parentSchool)
{
	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Name: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << team.name << endl
		 << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Setup date: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << team.setupDate << endl
		 << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Description: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << team.description << endl
		 << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Status: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << toString(team.status) << endl
		 << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Project: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << dereferenceElement(parentSchool.projects, team.project).name << endl;

	cout << getAnsiEscape(ANSI_ESCAPE::RESET);
}

void displayDetails(const PROJECT &project)
{
	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Name: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << project.name << endl
		 << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Description: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << project.description << endl
		 << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Status: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << toString(project.status) << endl
		 << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Number of assigned teams: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << project.teams.size() << endl;

	cout << getAnsiEscape(ANSI_ESCAPE::RESET);
}

void displayDetails(const SCHOOL &school)
{
	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Name: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << school.name << endl
		 << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "City: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << school.city << endl
		 << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Address: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << school.address << endl
		 << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Number of students: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << school.students.size() << endl
		 << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Number of teachers: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << school.teachers.size() << endl
		 << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Number of teams: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << school.teams.size() << endl
		 << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Number of projects: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << school.projects.size() << endl;

	cout << getAnsiEscape(ANSI_ESCAPE::RESET);
}
