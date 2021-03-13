#pragma once

#include "data_manip.h"
#include "structures.h"

#include <iostream>

enum class ANSI_ESCAPE
{
	RESET = 0,
	FG_BLACK = 30,
	FG_RED,
	FG_GREEN,
	FG_YELLOW,
	FG_BLUE,
	FG_MAGENTA,
	FG_CYAN,
	FG_WHITE,
	BG_BLACK = 40,
	BG_RED,
	BG_GREEN,
	BG_YELLOW,
	BG_BLUE,
	BG_MAGENTA,
	BG_CYAN,
	BG_WHITE,
	FG_B_BLACK = 90,
	FG_B_RED,
	FG_B_GREEN,
	FG_B_YELLOW,
	FG_B_BLUE,
	FG_B_MAGENTA,
	FG_B_CYAN,
	FG_B_WHITE,
	BG_B_BLACK = 100,
	BG_B_RED,
	BG_B_GREEN,
	BG_B_YELLOW,
	BG_B_BLUE,
	BG_B_MAGENTA,
	BG_B_CYAN,
	BG_B_WHITE
};

void listTable(const std::vector<SCHOOL> &schools);
void listTable(const std::unordered_map<std::string, STUDENT> &students, const SCHOOL &parentSchool);
void listTable(const std::unordered_map<std::string, TEACHER> &teachers, const SCHOOL &parentSchool);
void listTable(const std::unordered_map<size_t, TEAM> &teams, const SCHOOL &parentSchool);
void listTable(const std::unordered_map<std::string, PROJECT> &projects, const SCHOOL &parentSchool);
void listTable(const std::vector<TEAM_MEMBER> &members, const SCHOOL &parentSchool);
void listTable(const std::vector<size_t> &keys, const std::unordered_map<size_t, TEAM> &teams, const SCHOOL &parentSchool);
void listTable(const std::vector<std::string> &keys, const std::unordered_map<std::string, TEACHER> &teachers, const SCHOOL &parentSchool);

void clearConsole();
void printNewlines(size_t n);
bool getKey(size_t &key);
bool getKey(std::string &key);
void displayMenuOptions(const std::vector<const char *> &options);
void getMenuChoice(size_t &choice, size_t maxValue, size_t minValue = 1);
std::string getAnsiEscape(ANSI_ESCAPE colour);

bool menu(std::vector<SCHOOL> &schools);
bool menu(SCHOOL &school);
bool menu(STUDENT &student, const SCHOOL &parentSchool);
bool menu(TEACHER &teacher, const SCHOOL &parentSchool);
bool menu(TEAM &team, const SCHOOL &parentSchool);
bool menu(PROJECT &project, const SCHOOL &parentSchool);
bool menu(TEAM_MEMBER &member, const SCHOOL &parentSchool);

void menuSelect(std::vector<SCHOOL> &schools);
void menuAdd(std::vector<SCHOOL> &schools);
void menuRemove(std::vector<SCHOOL> &schools);
void menuRestore(std::vector<SCHOOL> &schools);
void menuStore(const std::vector<SCHOOL> &schools);

void menuAddAdditionalPrep(SCHOOL &school);
void menuAddAdditionalPrep(TEAM &team);
void menuAddAdditionalPrep(TEAM_MEMBER &member);

void menuEditCity(SCHOOL &school);
void menuEditAddress(SCHOOL &school);

void menuEditClass(STUDENT &student);
bool getStudentClass(unsigned &grade, char &classLetter);

void menuEditUsername(TEAM_MEMBER &member, const SCHOOL &parentSchool);
void menuEditRole(TEAM_MEMBER &member);

void menuEditProject(TEAM &team, const SCHOOL &parentSchool);

bool menuQueries(const SCHOOL &school);
void menuQueryTeachersWithoutTeam(const SCHOOL &school);

void displayDetails(const STUDENT &student);
void displayDetails(const TEACHER &teacher);
void displayDetails(const TEAM_MEMBER &member, const SCHOOL &parentSchool);
void displayDetails(const TEAM &team, const SCHOOL &parentSchool);
void displayDetails(const PROJECT &project);
void displayDetails(const SCHOOL &school);

template <typename T>
void menuDriver(T &element)
{
	clearConsole();
	printNewlines(1);

	while (menu(element)) {};
}

template <typename T>
void menuDriver(T &element, const SCHOOL &parentSchool)
{
	clearConsole();
	printNewlines(1);

	while (menu(element, parentSchool)) {};
}

template <typename T>
void menuSelect(std::vector<T> &v, const SCHOOL &parentSchool)
{
	size_t choice;

	if (v.empty()) {
		std::cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "There is currently nothing to select." << std::endl;
		return;
	}

	listTable(v, parentSchool);

	getMenuChoice(choice, v.size());

	menuDriver(dereferenceElement(v, v.begin() + (choice - 1)), parentSchool);
}

template <typename KEY, typename T>
void menuSelect(std::unordered_map<KEY, T> &m, const SCHOOL &parentSchool)
{
	std::vector<const KEY *> keys;

	size_t choice;

	if (m.empty()) {
		std::cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "There is currently nothing to select." << std::endl;
		return;
	}

	listTable(m, parentSchool);

	keys.reserve(m.size());
	for (auto it = m.begin(); it != m.end(); it++) {
		keys.push_back(&it->first);
	}

	getMenuChoice(choice, m.size());

	menuDriver(dereferenceElement(m, *keys[choice - 1]), parentSchool);
}

template <typename T>
void menuEditFirstName(T &element)
{
	using std::cin, std::cout, std::endl, std::getline;

	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Current first name: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << element.firstName << endl;
	cout << getAnsiEscape(ANSI_ESCAPE::FG_YELLOW) << "Enter new first name: " << getAnsiEscape(ANSI_ESCAPE::FG_B_YELLOW);
	getline(cin, element.firstName);

	clearConsole();
}

template <typename T>
void menuEditLastName(T &element)
{
	using std::cin, std::cout, std::endl, std::getline;

	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Current last name: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << element.lastName << endl;
	cout << getAnsiEscape(ANSI_ESCAPE::FG_YELLOW) << "Enter new last name: " << getAnsiEscape(ANSI_ESCAPE::FG_B_YELLOW);
	getline(cin, element.lastName);

	clearConsole();
}

template <typename T>
void menuEditEmail(T &element)
{
	using std::cin, std::cout, std::endl, std::getline;

	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Current email: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << element.email << endl;
	cout << getAnsiEscape(ANSI_ESCAPE::FG_YELLOW) << "Enter new email: " << getAnsiEscape(ANSI_ESCAPE::FG_B_YELLOW);
	getline(cin, element.email);

	clearConsole();
}

template <typename T>
void menuEditName(T &element)
{
	using std::cin, std::cout, std::endl, std::getline;

	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Current name: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << element.name << endl;
	cout << getAnsiEscape(ANSI_ESCAPE::FG_YELLOW) << "Enter new name: " << getAnsiEscape(ANSI_ESCAPE::FG_B_YELLOW);
	getline(cin, element.name);

	clearConsole();
}

template <typename T>
void menuEditDescription(T &element)
{
	using std::cin, std::cout, std::endl, std::getline;

	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Current description: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << element.description << endl;
	cout << getAnsiEscape(ANSI_ESCAPE::FG_YELLOW) << "Enter new description: (to end description, type | at the end of the last line)" << getAnsiEscape(ANSI_ESCAPE::FG_B_YELLOW) << endl;
	getline(cin, element.description, '|');
	cin.ignore();

	clearConsole();
}

template <typename T>
void menuEditStatus(T &element)
{
	using std::cin, std::cout, std::endl;

	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Legend:" << endl;
	for (int i = 0; i <= 1; i++) {
		cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << '(' << i << ") " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << toString((STATUS)i) << endl;
	}
	cout << endl;

	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Current status: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << (unsigned)element.status << endl;
	cout << getAnsiEscape(ANSI_ESCAPE::FG_YELLOW) << "Enter new status: " << getAnsiEscape(ANSI_ESCAPE::FG_B_YELLOW);

	try {
		getUnsignedNumber(cin, element.status, '\n', 1);
	}
	catch (...) {
		cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "Invalid input!" << endl;
		return;
	}

	clearConsole();
}

template <typename KEY, typename T>
void menuAdd(std::unordered_map<KEY, T> &m, const SCHOOL &parentSchool)
{
	using std::cin, std::cout, std::endl;

	KEY newKey;
	T newElement = {};

	cout << getAnsiEscape(ANSI_ESCAPE::FG_YELLOW) << "Enter unique key: " << getAnsiEscape(ANSI_ESCAPE::FG_B_YELLOW);
	if (!getKey(newKey)) {
		cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "Failed to add element: Invalid key!" << endl;
		return;
	}

	menuAddAdditionalPrep(newElement);

	if (!addElement(m, newKey, newElement)) {
		cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "Failed to add element: Key already exists!" << endl;
		return;
	}

	menuDriver(dereferenceElement(m, newKey), parentSchool);
}

template <typename T>
void menuAdd(std::vector<T> &v, const SCHOOL &parentSchool)
{
	using std::cout, std::endl;

	T newElement = {};

	menuAddAdditionalPrep(newElement);

	if (!addElement(v, newElement)) {
		cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "Failed to add element: Element already exists!" << endl;
		return;
	}

	menuDriver(dereferenceElement(v, v.end() - 1), parentSchool);
}

template <typename T>
void menuAddAdditionalPrep(T &element)
{
	// Dummy function
}

template <typename KEY, typename T>
void menuRemove(std::unordered_map<KEY, T> &m, const SCHOOL &parentSchool)
{
	std::vector<const KEY *> keys;

	size_t choice;

	if (m.empty()) {
		std::cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "There is currently nothing to remove." << std::endl;
		return;
	}

	listTable(m, parentSchool);

	keys.reserve(m.size());
	for (auto it = m.begin(); it != m.end(); it++) {
		keys.push_back(&it->first);
	}

	getMenuChoice(choice, m.size());

	deleteElement(m, *keys[choice - 1]);

	clearConsole();
}

template <typename T>
void menuRemove(std::vector<T> &v, const SCHOOL &parentSchool)
{
	using std::cout, std::endl;

	size_t choice;

	if (v.empty()) {
		std::cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "There is currently nothing to remove." << std::endl;
		return;
	}

	listTable(v, parentSchool);

	getMenuChoice(choice, v.size());

	deleteElement(v, choice - 1);

	clearConsole();
}

template <typename KEY, typename T>
void menuLink(std::vector<KEY> &linkedElements, const std::unordered_map<KEY, T> &allElements, const SCHOOL &parentSchool)
{
	std::vector<const KEY *> keys;

	using std::cout, std::endl;

	size_t choice;

	if (allElements.empty()) {
		cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "There is currently nothing to select." << endl;
		return;
	}

	cout << "Choose from the list: " << endl;
	printNewlines(1);

	listTable(allElements, parentSchool);

	keys.reserve(allElements.size());
	for (auto it = allElements.begin(); it != allElements.end(); it++) {
		keys.push_back(&it->first);
	}

	getMenuChoice(choice, allElements.size());

	clearConsole();

	if (!addElement(linkedElements, *keys[choice - 1])) {
		cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "Failed to link!" << endl;
		return;
	}
}

template <typename KEY, typename T>
void menuUnlink(std::vector<KEY> &linkedElements, const std::unordered_map<KEY, T> &allElements, const SCHOOL &parentSchool)
{
	std::vector<const KEY *> keys;

	using std::cout, std::endl;

	size_t choice;

	if (allElements.empty()) {
		cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "There is currently nothing to select." << endl;
		return;
	}

	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Choose from the list: " << endl;
	printNewlines(1);

	listTable(linkedElements, allElements, parentSchool);

	keys.reserve(linkedElements.size());
	for (auto it = linkedElements.begin(); it != linkedElements.end(); it++) {
		keys.push_back(&*it);
	}

	getMenuChoice(choice, linkedElements.size());

	clearConsole();

	if (!deleteElement(linkedElements, *keys[choice - 1])) {
		cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "Failed to unlink!" << endl;
		return;
	}
}
