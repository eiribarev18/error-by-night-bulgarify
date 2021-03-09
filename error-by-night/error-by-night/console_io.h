#pragma once

#include "data_manip.h"
#include "structures.h"

#include <iostream>

void listTable(const std::vector<SCHOOL> &schools);
void listTable(const std::unordered_map<std::string, STUDENT> &students, const SCHOOL &parentSchool);
void listTable(const std::unordered_map<std::string, TEACHER> &teachers, const SCHOOL &parentSchool);
void listTable(const std::unordered_map<size_t, TEAM> &teams, const SCHOOL &parentSchool);
void listTable(const std::unordered_map<std::string, PROJECT> &projects, const SCHOOL &parentSchool);
void listTable(const std::vector<TEAM_MEMBER> &members, const SCHOOL &parentSchool);

void listTable(const std::vector<size_t> &keys, const std::unordered_map<size_t, TEAM> &teams, const SCHOOL &parentSchool);

void clearConsole();
void printNewlines(size_t n);
bool getKey(size_t &key);
bool getKey(std::string &key);

void getMenuChoice(size_t &choice, size_t maxValue, size_t minValue = 1);

bool menu(std::vector<SCHOOL> &schools);

void menuSelect(std::vector<SCHOOL> &schools);
void menuAdd(std::vector<SCHOOL> &schools);
void menuAddAdditionalPrep(SCHOOL &school);
void menuRemove(std::vector<SCHOOL> &schools);
void menuRestore(std::vector<SCHOOL> &schools);
void menuStore(const std::vector<SCHOOL> &schools);

bool menu(SCHOOL &school);

void menuEditCity(SCHOOL &school);
void menuEditAddress(SCHOOL &school);

bool menu(STUDENT &student, const SCHOOL &parentSchool);

void menuEditClass(STUDENT &student);
bool getStudentClass(unsigned &grade, char &classLetter);

bool menu(TEACHER &teacher, const SCHOOL &parentSchool);

bool menu(TEAM &team, const SCHOOL &parentSchool);

void menuAddAdditionalPrep(TEAM &team);

bool menu(PROJECT &project, const SCHOOL &parentSchool);

bool menu(TEAM_MEMBER &member, const SCHOOL &parentSchool);

void menuAddAdditionalPrep(TEAM_MEMBER &member);

void menuEditRole(TEAM_MEMBER &member);

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
		std::cout << "There is currently nothing to select." << std::endl;
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
		std::cout << "There is currently nothing to select." << std::endl;
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

	cout << "Current first name: " << element.firstName << endl;
	cout << "Enter new first name: ";
	getline(cin, element.firstName);

	clearConsole();
}

template <typename T>
void menuEditLastName(T &element)
{
	using std::cin, std::cout, std::endl, std::getline;

	cout << "Current last name: " << element.lastName << endl;
	cout << "Enter new last name: ";
	getline(cin, element.lastName);

	clearConsole();
}

template <typename T>
void menuEditEmail(T &element)
{
	using std::cin, std::cout, std::endl, std::getline;

	cout << "Current email: " << element.email << endl;
	cout << "Enter new email: ";
	getline(cin, element.email);

	clearConsole();
}

template <typename T>
void menuEditName(T &element)
{
	using std::cin, std::cout, std::endl, std::getline;

	cout << "Current name: " << element.name << endl;
	cout << "Enter new name: ";
	getline(cin, element.name);

	clearConsole();
}

template <typename T>
void menuEditDescription(T &element)
{
	using std::cin, std::cout, std::endl, std::getline;

	cout << "Current description: " << element.description << endl;
	cout << "Enter new description: ";
	getline(cin, element.description);

	clearConsole();
}

template <typename T>
void menuEditStatus(T &element)
{
	using std::cin, std::cout, std::endl;

	cout << "Legend:" << endl;
	for (int i = 0; i <= 1; i++) {
		cout << '(' << i << ") " << toString((STATUS)i) << endl;
	}
	cout << endl;

	cout << "Current status: " << (unsigned)element.status << endl;
	cout << "Enter new status: ";

	try {
		getUnsignedNumber(cin, element.status, '\n', 1);
	}
	catch (...) {
		cout << "Invalid input!" << endl;
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

	cout << "Enter unique key: ";
	if (!getKey(newKey)) {
		cout << "Failed to add element: Invalid key!" << endl;
		return;
	}

	menuAddAdditionalPrep(newElement);

	if (!addElement(m, newKey, newElement)) {
		cout << "Failed to add element: Key already exists!" << endl;
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
		cout << "Failed to add element: Element already exists!" << endl;
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
		std::cout << "There is currently nothing to remove." << std::endl;
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
		std::cout << "There is currently nothing to remove." << std::endl;
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
		cout << "There is currently nothing to select." << endl;
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
		cout << "Failed to link!" << endl;
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
		cout << "There is currently nothing to select." << endl;
		return;
	}

	cout << "Choose from the list: " << endl;
	printNewlines(1);

	listTable(linkedElements, allElements, parentSchool);

	keys.reserve(linkedElements.size());
	for (auto it = linkedElements.begin(); it != linkedElements.end(); it++) {
		keys.push_back(&*it);
	}

	getMenuChoice(choice, linkedElements.size());

	clearConsole();

	if (!deleteElement(linkedElements, *keys[choice - 1])) {
		cout << "Failed to unlink!" << endl;
		return;
	}
}
