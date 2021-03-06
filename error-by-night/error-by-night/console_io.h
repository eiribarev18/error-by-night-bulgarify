#pragma once

#include "structures.h"

#include <iostream>

void listTable(const std::vector<SCHOOL> &schools);
void listTable(const std::unordered_map<std::string, STUDENT> &students, const SCHOOL &parentSchool);
void listTable(const std::unordered_map<std::string, TEACHER> &teachers, const SCHOOL &parentSchool);
void listTable(const std::unordered_map<size_t, TEAM> &teams, const SCHOOL &parentSchool);
void listTable(const std::unordered_map<std::string, PROJECT> &projects, const SCHOOL &parentSchool);

void getMenuChoice(size_t &choice, size_t optionCount);

bool menu(std::vector<SCHOOL> &schools);

void menuSelect(std::vector<SCHOOL> &schools);
void menuRestore(std::vector<SCHOOL> &schools);
void menuStore(const std::vector<SCHOOL> &schools);

bool menu(SCHOOL &school);

void menuEditName(SCHOOL &school);
void menuEditCity(SCHOOL &school);
void menuEditAddress(SCHOOL &school);

bool menu(STUDENT &student, const SCHOOL &parentSchool);

void menuEditFirstName(STUDENT &student);
void menuEditLastName(STUDENT &student);
void menuEditEmail(STUDENT &student);

bool menu(TEACHER &teacher, const SCHOOL &parentSchool);

void menuEditFirstName(TEACHER &teacher);
void menuEditLastName(TEACHER &teacher);
void menuEditEmail(TEACHER &teacher);

bool menu(TEAM &team, const SCHOOL &parentSchool);

bool menu(PROJECT &project, const SCHOOL &parentSchool);

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

	menuDriver(dereferenceElement(m, m.find(*keys[choice - 1])), parentSchool);
}
