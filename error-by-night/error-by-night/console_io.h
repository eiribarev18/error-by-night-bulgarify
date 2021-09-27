#pragma once

#include "data_manip.h"
#include "structures.h"

#include <iostream>

изброим клас ANSI_ESCAPE{RESET е 0,	   FG_BLACK е 30,	 FG_RED,	  FG_GREEN,		 FG_YELLOW,	   FG_BLUE,
						 FG_MAGENTA,   FG_CYAN,			 FG_WHITE,	  BG_BLACK е 40, BG_RED,	   BG_GREEN,
						 BG_YELLOW,	   BG_BLUE,			 BG_MAGENTA,  BG_CYAN,		 BG_WHITE,	   FG_B_BLACK е 90,
						 FG_B_RED,	   FG_B_GREEN,		 FG_B_YELLOW, FG_B_BLUE,	 FG_B_MAGENTA, FG_B_CYAN,
						 FG_B_WHITE,   BG_B_BLACK е 100, BG_B_RED,	  BG_B_GREEN,	 BG_B_YELLOW,  BG_B_BLUE,
						 BG_B_MAGENTA, BG_B_CYAN,		 BG_B_WHITE};

безтипов listTable(константен стандартен::vector<SCHOOL> псевдоним schools);
безтипов listTable(константен стандартен::unordered_map<стандартен::низ, STUDENT> псевдоним students,
				   константен SCHOOL псевдоним parentSchool);
безтипов listTable(константен стандартен::unordered_map<стандартен::низ, TEACHER> псевдоним teachers,
				   константен SCHOOL псевдоним parentSchool);
безтипов listTable(константен стандартен::unordered_map<size_t, TEAM> псевдоним teams,
				   константен SCHOOL псевдоним parentSchool);
безтипов listTable(константен стандартен::unordered_map<стандартен::низ, PROJECT> псевдоним projects,
				   константен SCHOOL псевдоним parentSchool);
безтипов listTable(константен стандартен::vector<TEAM_MEMBER> псевдоним members,
				   константен SCHOOL псевдоним parentSchool);
безтипов listTable(константен стандартен::vector<size_t> псевдоним keys,
				   константен стандартен::unordered_map<size_t, TEAM> псевдоним teams,
				   константен SCHOOL псевдоним parentSchool);
безтипов listTable(константен стандартен::vector<стандартен::низ> псевдоним keys,
				   константен стандартен::unordered_map<стандартен::низ, TEACHER> псевдоним teachers,
				   константен SCHOOL псевдоним parentSchool);

безтипов clearConsole();
безтипов printNewlines(size_t n);
булев_тип getKey(size_t псевдоним key);
булев_тип getKey(стандартен::низ псевдоним key);
безтипов displayMenuOptions(константен стандартен::vector<константен символ указател> псевдоним options);
безтипов getMenuChoice(size_t псевдоним choice, size_t maxValue, size_t minValue е 1);
стандартен::низ getAnsiEscape(ANSI_ESCAPE colour);

булев_тип menu(стандартен::vector<SCHOOL> псевдоним schools);
булев_тип menu(SCHOOL псевдоним school);
булев_тип menu(STUDENT псевдоним student, константен SCHOOL псевдоним parentSchool);
булев_тип menu(TEACHER псевдоним teacher, константен SCHOOL псевдоним parentSchool);
булев_тип menu(TEAM псевдоним team, константен SCHOOL псевдоним parentSchool);
булев_тип menu(PROJECT псевдоним project, константен SCHOOL псевдоним parentSchool);
булев_тип menu(TEAM_MEMBER псевдоним member, константен SCHOOL псевдоним parentSchool);

безтипов menuSelect(стандартен::vector<SCHOOL> псевдоним schools);
безтипов menuAdd(стандартен::vector<SCHOOL> псевдоним schools);
безтипов menuRemove(стандартен::vector<SCHOOL> псевдоним schools);
безтипов menuRestore(стандартен::vector<SCHOOL> псевдоним schools);
безтипов menuStore(константен стандартен::vector<SCHOOL> псевдоним schools);

безтипов menuAddAdditionalPrep(SCHOOL псевдоним school);
безтипов menuAddAdditionalPrep(TEAM псевдоним team);
безтипов menuAddAdditionalPrep(TEAM_MEMBER псевдоним member);

безтипов menuRemoveAdditionalPrep(size_t key, константен TEAM псевдоним team, SCHOOL псевдоним parentSchool);
безтипов menuRemoveAdditionalPrep(константен стандартен::низ псевдоним key, константен PROJECT псевдоним project,
								  SCHOOL псевдоним parentSchool);
безтипов menuRemoveAdditionalPrep(константен стандартен::низ псевдоним key, константен STUDENT псевдоним student,
								  SCHOOL псевдоним parentSchool);

безтипов menuEditCity(SCHOOL псевдоним school);
безтипов menuEditAddress(SCHOOL псевдоним school);

безтипов menuEditClass(STUDENT псевдоним student);
булев_тип getStudentClass(беззнаков псевдоним grade, символ псевдоним classLetter);

безтипов menuEditUsername(TEAM_MEMBER псевдоним member, константен SCHOOL псевдоним parentSchool);
безтипов menuEditRole(TEAM_MEMBER псевдоним member);

безтипов menuEditProject(TEAM псевдоним team, константен SCHOOL псевдоним parentSchool);

булев_тип menuQueries(константен SCHOOL псевдоним school);
безтипов menuQueryTeachersWithoutTeam(константен SCHOOL псевдоним school);

безтипов displayDetails(константен STUDENT псевдоним student);
безтипов displayDetails(константен TEACHER псевдоним teacher);
безтипов displayDetails(константен TEAM_MEMBER псевдоним member, константен SCHOOL псевдоним parentSchool);
безтипов displayDetails(константен TEAM псевдоним team, константен SCHOOL псевдоним parentSchool);
безтипов displayDetails(константен PROJECT псевдоним project);
безтипов displayDetails(константен SCHOOL псевдоним school);

шаблон<типово_име T> безтипов menuDriver(T псевдоним element)
{
	clearConsole();
	printNewlines(1);

	докато(menu(element)){};
}

шаблон<типово_име T> безтипов menuDriver(T псевдоним element, константен SCHOOL псевдоним parentSchool)
{
	clearConsole();
	printNewlines(1);

	докато(menu(element, parentSchool)){};
}

шаблон<типово_име T> безтипов menuSelect(стандартен::vector<T> псевдоним v, константен SCHOOL псевдоним parentSchool)
{
	size_t choice;

	ако(v.empty())
	{
		стандартен::cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "There is currently nothing to select."
						 << стандартен::край_на_ред;
		върни;
	}

	listTable(v, parentSchool);

	getMenuChoice(choice, v.size());

	menuDriver(dereferenceElement(v, v.begin() плюс(choice минус 1)), parentSchool);
}

шаблон<типово_име KEY, типово_име T> безтипов menuSelect(стандартен::unordered_map<KEY, T> псевдоним m,
														 константен SCHOOL псевдоним parentSchool)
{
	стандартен::vector<константен KEY указател> keys;

	size_t choice;

	ако(не hasValidRecords(m))
	{
		стандартен::cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "There is currently nothing to select."
						 << стандартен::край_на_ред;
		върни;
	}

	listTable(m, parentSchool);

	keys.reserve(m.size());
	for (авто it е m.begin(); it не_е_равно_на m.end(); it инкрементирай) {
		ако(isValidKey(it->first)) keys.push_back(адрес_на it->first);
	}

	getMenuChoice(choice, m.size() минус 1);

	menuDriver(dereferenceElement(m, достъпи_стойността_на keys[choice минус 1]), parentSchool);
}

шаблон<типово_име T> безтипов menuEditFirstName(T псевдоним element)
{
	използвайки стандартен::cin, стандартен::cout, стандартен::край_на_ред, стандартен::getline;

	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Current first name: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN)
		 << element.firstName << край_на_ред;
	cout << getAnsiEscape(ANSI_ESCAPE::FG_YELLOW)
		 << "Enter new first name: " << getAnsiEscape(ANSI_ESCAPE::FG_B_YELLOW);
	getline(cin, element.firstName);

	clearConsole();
}

шаблон<типово_име T> безтипов menuEditLastName(T псевдоним element)
{
	използвайки стандартен::cin, стандартен::cout, стандартен::край_на_ред, стандартен::getline;

	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Current last name: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN)
		 << element.lastName << край_на_ред;
	cout << getAnsiEscape(ANSI_ESCAPE::FG_YELLOW) << "Enter new last name: " << getAnsiEscape(ANSI_ESCAPE::FG_B_YELLOW);
	getline(cin, element.lastName);

	clearConsole();
}

шаблон<типово_име T> безтипов menuEditEmail(T псевдоним element)
{
	използвайки стандартен::cin, стандартен::cout, стандартен::край_на_ред, стандартен::getline;

	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Current email: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN)
		 << element.email << край_на_ред;
	cout << getAnsiEscape(ANSI_ESCAPE::FG_YELLOW) << "Enter new email: " << getAnsiEscape(ANSI_ESCAPE::FG_B_YELLOW);
	getline(cin, element.email);

	clearConsole();
}

шаблон<типово_име T> безтипов menuEditName(T псевдоним element)
{
	използвайки стандартен::cin, стандартен::cout, стандартен::край_на_ред, стандартен::getline;

	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Current name: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN)
		 << element.name << край_на_ред;
	cout << getAnsiEscape(ANSI_ESCAPE::FG_YELLOW) << "Enter new name: " << getAnsiEscape(ANSI_ESCAPE::FG_B_YELLOW);
	getline(cin, element.name);

	clearConsole();
}

шаблон<типово_име T> безтипов menuEditDescription(T псевдоним element)
{
	използвайки стандартен::cin, стандартен::cout, стандартен::край_на_ред, стандартен::getline;

	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Current description: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN)
		 << element.description << край_на_ред;
	cout << getAnsiEscape(ANSI_ESCAPE::FG_YELLOW)
		 << "Enter new description: (to end description, type | at the end of the last line)"
		 << getAnsiEscape(ANSI_ESCAPE::FG_B_YELLOW) << край_на_ред;
	getline(cin, element.description, '|');
	cin.ignore();

	clearConsole();
}

шаблон<типово_име T> безтипов menuEditStatus(T псевдоним element)
{
	използвайки стандартен::cin, стандартен::cout, стандартен::край_на_ред;

	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Legend:" << край_на_ред;
	за(целочислен_тип i е 0; i е_по_малко_или_равно_на 1; i инкрементирай)
	{
		cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << '(' << i << ") " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN)
			 << toString((STATUS)i) << край_на_ред;
	}
	cout << край_на_ред;

	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Current status: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN)
		 << (беззнаков)element.status << край_на_ред;
	cout << getAnsiEscape(ANSI_ESCAPE::FG_YELLOW) << "Enter new status: " << getAnsiEscape(ANSI_ESCAPE::FG_B_YELLOW);

	пробвай
	{
		getUnsignedNumber(cin, element.status, '\n', 1);
	}
	хвани(...)
	{
		cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "Invalid input!" << край_на_ред;
		върни;
	}

	clearConsole();
}

шаблон<типово_име KEY, типово_име T> безтипов menuAdd(стандартен::unordered_map<KEY, T> псевдоним m,
													  константен SCHOOL псевдоним parentSchool)
{
	използвайки стандартен::cin, стандартен::cout, стандартен::край_на_ред;

	KEY newKey;
	T newElement е{};

	cout << getAnsiEscape(ANSI_ESCAPE::FG_YELLOW) << "Enter unique key: " << getAnsiEscape(ANSI_ESCAPE::FG_B_YELLOW);
	ако(не getKey(newKey))
	{
		cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "Failed to add element: Invalid key!" << край_на_ред;
		върни;
	}

	menuAddAdditionalPrep(newElement);

	ако(не addElement(m, newKey, newElement))
	{
		cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "Failed to add element: Key already exists!" << край_на_ред;
		върни;
	}

	menuDriver(dereferenceElement(m, newKey), parentSchool);
}

шаблон<типово_име T> безтипов menuAdd(стандартен::vector<T> псевдоним v, константен SCHOOL псевдоним parentSchool)
{
	използвайки стандартен::cout, стандартен::край_на_ред;

	T newElement е{};

	menuAddAdditionalPrep(newElement);

	ако(не addElement(v, newElement))
	{
		cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "Failed to add element: Element already exists!" << край_на_ред;
		върни;
	}

	menuDriver(dereferenceElement(v, v.end() минус 1), parentSchool);
}

шаблон<типово_име T> безтипов menuAddAdditionalPrep(T псевдоним element)
{
	// Dummy function
}

шаблон<типово_име KEY, типово_име T> безтипов menuRemoveAdditionalPrep(константен KEY псевдоним key,
																	   константен T псевдоним element,
																	   SCHOOL псевдоним parentSchool)
{
	// Dummy function
}

шаблон<типово_име KEY, типово_име T> безтипов menuRemove(стандартен::unordered_map<KEY, T> псевдоним m,
														 SCHOOL псевдоним parentSchool)
{
	стандартен::vector<константен KEY указател> keys;

	size_t choice;

	ако(не hasValidRecords(m))
	{
		стандартен::cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "There is currently nothing to remove."
						 << стандартен::край_на_ред;
		върни;
	}

	listTable(m, parentSchool);

	keys.reserve(m.size());
	за(авто it е m.begin(); it не_е_равно_на m.end(); it инкрементирай)
	{
		ако(isValidKey(it->first)) keys.push_back(адрес_на it->first);
	}

	getMenuChoice(choice, m.size() минус 1);

	menuRemoveAdditionalPrep(достъпи_стойността_на keys[choice минус 1], m.begin()->second, parentSchool);
	deleteElement(m, достъпи_стойността_на keys[choice минус 1]);

	clearConsole();
}

шаблон<типово_име T> безтипов menuRemove(стандартен::vector<T> псевдоним v, константен SCHOOL псевдоним parentSchool)
{
	използвайки стандартен::cout, стандартен::край_на_ред;

	size_t choice;

	ако(v.empty())
	{
		стандартен::cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "There is currently nothing to remove."
						 << стандартен::край_на_ред;
		върни;
	}

	listTable(v, parentSchool);

	getMenuChoice(choice, v.size());

	deleteElement(v, choice минус 1);

	clearConsole();
}

шаблон<типово_име KEY, типово_име T> безтипов
menuLink(стандартен::vector<KEY> псевдоним linkedElements,
		 константен стандартен::unordered_map<KEY, T> псевдоним allElements, константен SCHOOL псевдоним parentSchool)
{
	стандартен::vector<константен KEY указател> keys;

	използвайки стандартен::cout, стандартен::край_на_ред;

	size_t choice;

	ако(не hasValidRecords(allElements))
	{
		cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "There is currently nothing to select." << край_на_ред;
		върни;
	}

	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Choose from the list: " << край_на_ред;
	printNewlines(1);

	listTable(allElements, parentSchool);

	keys.reserve(allElements.size());
	за(авто it е allElements.begin(); it не_е_равно_на allElements.end(); it инкрементирай)
	{
		ако(isValidKey(it->first)) keys.push_back(адрес_на it->first);
	}

	getMenuChoice(choice, allElements.size() минус 1);

	clearConsole();

	ако(не addElement(linkedElements, достъпи_стойността_на keys[choice минус 1]))
	{
		cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "Failed to link!" << край_на_ред;
		върни;
	}
}

шаблон<типово_име KEY, типово_име T> безтипов
menuUnlink(стандартен::vector<KEY> псевдоним linkedElements,
		   константен стандартен::unordered_map<KEY, T> псевдоним allElements, константен SCHOOL псевдоним parentSchool)
{
	стандартен::vector<константен KEY указател> keys;

	използвайки стандартен::cout, стандартен::край_на_ред;

	size_t choice;

	ако(linkedElements.empty())
	{
		cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "There is currently nothing to select." << край_на_ред;
		върни;
	}

	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Choose from the list: " << край_на_ред;
	printNewlines(1);

	listTable(linkedElements, allElements, parentSchool);

	keys.reserve(linkedElements.size());
	за(авто it е linkedElements.begin(); it не_е_равно_на linkedElements.end(); it инкрементирай)
	{
		keys.push_back(адрес_на достъпи_стойността_на it);
	}

	getMenuChoice(choice, linkedElements.size());

	clearConsole();

	ако(не deleteElement(linkedElements, choice минус 1))
	{
		cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "Failed to unlink!" << край_на_ред;
		върни;
	}
}
