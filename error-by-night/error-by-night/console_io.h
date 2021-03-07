#pragma once

#include "structures.h"

#include <iostream>

void listTable(const std::vector<SCHOOL> &schools);
void listTable(const std::unordered_map<std::string, STUDENT> &students, const SCHOOL &parentSchool);
void listTable(const std::unordered_map<std::string, TEACHER> &teachers, const SCHOOL &parentSchool);
void listTable(const std::unordered_map<size_t, TEAM> &teams, const SCHOOL &parentSchool);
void listTable(const std::unordered_map<std::string, PROJECT> &projects, const SCHOOL &parentSchool);
void listTable(const std::vector<TEAM_MEMBER> &members, const SCHOOL &parentSchool);

void listTable(const std::vector<size_t> &keys, const std::unordered_map<size_t, TEAM> &teams, const SCHOOL &parentSchool);

void getMenuChoice(size_t &choice, size_t maxValue, size_t minValue = 1);

bool menu(std::vector<SCHOOL> &schools);

void menuSelect(std::vector<SCHOOL> &schools);
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

bool menu(PROJECT &project, const SCHOOL &parentSchool);

bool menu(TEAM_MEMBER &member, const SCHOOL &parentSchool);

void menuEditRole(TEAM_MEMBER &member);

template <typename T>
void menuDriver(T &element)
{
	while (menu(element)) {};
}

template <typename T>
void menuDriver(T &element, const SCHOOL &parentSchool)
{
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
}

template <typename T>
void menuEditLastName(T &element)
{
	using std::cin, std::cout, std::endl, std::getline;

	cout << "Current last name: " << element.lastName << endl;
	cout << "Enter new last name: ";
	getline(cin, element.lastName);
}

template <typename T>
void menuEditEmail(T &element)
{
	using std::cin, std::cout, std::endl, std::getline;

	cout << "Current email: " << element.email << endl;
	cout << "Enter new email: ";
	getline(cin, element.email);
}

template <typename T>
void menuEditName(T &element)
{
	using std::cin, std::cout, std::endl, std::getline;

	cout << "Current name: " << element.name << endl;
	cout << "Enter new name: ";
	getline(cin, element.name);
}

template <typename T>
void menuEditDescription(T &element)
{
	using std::cin, std::cout, std::endl, std::getline;

	cout << "Current description: " << element.description << endl;
	cout << "Enter new description: ";
	getline(cin, element.description);
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
	}
}
