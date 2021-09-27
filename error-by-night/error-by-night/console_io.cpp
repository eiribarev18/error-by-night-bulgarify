#include "console_io.h"

#include "data_manip.h"
#include "file_io.h"

#include <cmath>
#include <ctime>
#include <iomanip>
#include <sstream>

използвайки имево_пространство стандартен;

безтипов printNewlines(size_t n)
{
	за(size_t i е 0; i е_по_малко_от n; i инкрементирай)
	{
		cout << endl;
	}
}

булев_тип getKey(size_t псевдоним key)
{
	пробвай
	{
		getUnsignedNumber(cin, key);
	}
	хвани(...)
	{
		върни грешно;
	}

	върни вярно;
}

булев_тип getKey(низ псевдоним key)
{
	getline(cin, key);

	върни вярно;
}

безтипов displayMenuOptions(константен vector<константен символ указател> псевдоним options)
{
	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN);

	за(size_t i е 0; i е_по_малко_от options.size(); i инкрементирай)
	{
		cout << i плюс 1 << ". " << options[i] << endl;
	}

	cout << getAnsiEscape(ANSI_ESCAPE::RESET);
}

безтипов getMenuChoice(size_t псевдоним choice, size_t maxValue, size_t minValue)
{
	cout << getAnsiEscape(ANSI_ESCAPE::FG_YELLOW);

	while (вярно) {
		cout << "Enter choice (" << minValue << " - " << maxValue << "): " << getAnsiEscape(ANSI_ESCAPE::FG_B_YELLOW);
		пробвай
		{
			getUnsignedNumber(cin, choice, '\n', maxValue, minValue);
		}
		хвани(...)
		{
			cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "Invalid input!" << getAnsiEscape(ANSI_ESCAPE::FG_YELLOW)
				 << endl;
			continue;
		}
		break;
	}

	cout << getAnsiEscape(ANSI_ESCAPE::RESET);
}

булев_тип menu(vector<SCHOOL> псевдоним schools)
{
	size_t choice;
	vector<константен символ указател> options е{"Select school",
												 "List schools",
												 "Add school",
												 "Remove school",
												 "Restore from backup",
												 "Store to backup",
												 "Quit"};

	displayMenuOptions(options);
	getMenuChoice(choice, options.size());

	clearConsole();

	превключвател(choice)
	{
		случай 1 : menuSelect(schools);
		break;
		случай 2 : listTable(schools);
		break;
		случай 3 : menuAdd(schools);
		break;
		случай 4 : menuRemove(schools);
		break;
		случай 5 : menuRestore(schools);
		break;
		случай 6 : menuStore(schools);
		break;
		случай 7 : върни грешно;
	}

	printNewlines(1);

	върни вярно;
}

булев_тип menu(SCHOOL псевдоним school)
{
	size_t choice;
	vector<константен символ указател> options е{
		"Edit name",	  "Edit city",	   "Edit address",	 "Select student", "Select teacher", "Select team",
		"Select project", "List students", "List teachers",	 "List teams",	   "List projects",	 "Add student",
		"Add teacher",	  "Add team",	   "Add project",	 "Remove student", "Remove teacher", "Remove team",
		"Remove project", "Queries",	   "Back to schools"};

	displayDetails(school);
	printNewlines(1);

	displayMenuOptions(options);
	getMenuChoice(choice, options.size());

	clearConsole();

	превключвател(choice)
	{
		случай 1 : menuEditName(school);
		break;
		случай 2 : menuEditCity(school);
		break;
		случай 3 : menuEditAddress(school);
		break;
		случай 4 : menuSelect(school.students, school);
		break;
		случай 5 : menuSelect(school.teachers, school);
		break;
		случай 6 : menuSelect(school.teams, school);
		break;
		случай 7 : menuSelect(school.projects, school);
		break;
		случай 8 : listTable(school.students, school);
		break;
		случай 9 : listTable(school.teachers, school);
		break;
		случай 10 : listTable(school.teams, school);
		break;
		случай 11 : listTable(school.projects, school);
		break;
		случай 12 : menuAdd(school.students, school);
		break;
		случай 13 : menuAdd(school.teachers, school);
		break;
		случай 14 : menuAdd(school.teams, school);
		break;
		случай 15 : menuAdd(school.projects, school);
		break;
		случай 16 : menuRemove(school.students, school);
		break;
		случай 17 : menuRemove(school.teachers, school);
		break;
		случай 18 : menuRemove(school.teams, school);
		break;
		случай 19 : menuRemove(school.projects, school);
		break;
		случай 20 : while (menuQueries(school)){};
		break;
		случай 21 : върни грешно;
	}

	printNewlines(1);

	върни вярно;
}

булев_тип menu(STUDENT псевдоним student, константен SCHOOL псевдоним parentSchool)
{
	size_t choice;
	vector<константен символ указател> options е{
		"Edit first name", "Edit last name", "Edit email", "Edit class", "Back to school"};

	displayDetails(student);
	printNewlines(1);

	displayMenuOptions(options);
	getMenuChoice(choice, options.size());

	clearConsole();

	превключвател(choice)
	{
		случай 1 : menuEditFirstName(student);
		break;
		случай 2 : menuEditLastName(student);
		break;
		случай 3 : menuEditEmail(student);
		break;
		случай 4 : menuEditClass(student);
		break;
		случай 5 : върни грешно;
	}

	printNewlines(1);

	върни вярно;
}

булев_тип menu(TEACHER псевдоним teacher, константен SCHOOL псевдоним parentSchool)
{
	size_t choice;
	vector<константен символ указател> options е{"Edit first name",
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

	превключвател(choice)
	{
		случай 1 : menuEditFirstName(teacher);
		break;
		случай 2 : menuEditLastName(teacher);
		break;
		случай 3 : menuEditEmail(teacher);
		break;
		случай 4 : listTable(teacher.teams, parentSchool.teams, parentSchool);
		break;
		случай 5 : menuLink(teacher.teams, parentSchool.teams, parentSchool);
		break;
		случай 6 : menuUnlink(teacher.teams, parentSchool.teams, parentSchool);
		break;
		случай 7 : върни грешно;
	}

	printNewlines(1);

	върни вярно;
}

булев_тип menu(TEAM псевдоним team, константен SCHOOL псевдоним parentSchool)
{
	size_t choice;
	vector<константен символ указател> options е{"Edit name",
												 "Edit description",
												 "Edit status",
												 "Change project",
												 "Select member",
												 "List members",
												 "Add member",
												 "Delete member",
												 "Back to school"};

	displayDetails(team, parentSchool);
	printNewlines(1);

	displayMenuOptions(options);
	getMenuChoice(choice, options.size());

	clearConsole();

	превключвател(choice)
	{
		случай 1 : menuEditName(team);
		break;
		случай 2 : menuEditDescription(team);
		break;
		случай 3 : menuEditStatus(team);
		break;
		случай 4 : menuEditProject(team, parentSchool);
		break;
		случай 5 : menuSelect(team.members, parentSchool);
		break;
		случай 6 : listTable(team.members, parentSchool);
		break;
		случай 7 : menuAdd(team.members, parentSchool);
		break;
		случай 8 : menuRemove(team.members, parentSchool);
		break;
		случай 9 : върни грешно;
	}

	printNewlines(1);

	върни вярно;
}

булев_тип menu(PROJECT псевдоним project, константен SCHOOL псевдоним parentSchool)
{
	size_t choice;
	vector<константен символ указател> options е{
		"Edit name", "Edit description", "Edit status", "List teams", "Assign team", "Dismiss team", "Back to school"};

	displayDetails(project);
	printNewlines(1);

	displayMenuOptions(options);
	getMenuChoice(choice, options.size());

	clearConsole();

	превключвател(choice)
	{
		случай 1 : menuEditName(project);
		break;
		случай 2 : menuEditDescription(project);
		break;
		случай 3 : menuEditStatus(project);
		break;
		случай 4 : listTable(project.teams, parentSchool.teams, parentSchool);
		break;
		случай 5 : menuLink(project.teams, parentSchool.teams, parentSchool);
		break;
		случай 6 : menuUnlink(project.teams, parentSchool.teams, parentSchool);
		break;
		случай 7 : върни грешно;
	}

	printNewlines(1);

	върни вярно;
}

булев_тип menu(TEAM_MEMBER псевдоним member, константен SCHOOL псевдоним parentSchool)
{
	size_t choice;
	vector<константен символ указател> options е{"Change student", "Edit role", "Back to team"};

	displayDetails(member, parentSchool);
	printNewlines(1);

	displayMenuOptions(options);
	getMenuChoice(choice, options.size());

	clearConsole();

	превключвател(choice)
	{
		случай 1 : menuEditUsername(member, parentSchool);
		break;
		случай 2 : menuEditRole(member);
		break;
		случай 3 : върни грешно;
	}

	printNewlines(1);

	върни вярно;
}

безтипов menuSelect(vector<SCHOOL> псевдоним schools)
{
	size_t choice;

	clearConsole();

	ако(schools.empty())
	{
		std::cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "There is currently nothing to select." << std::endl;
		върни;
	}

	listTable(schools);

	getMenuChoice(choice, schools.size());

	menuDriver(dereferenceElement(schools, schools.begin() плюс(choice минус 1)));
}

безтипов menuAdd(vector<SCHOOL> псевдоним schools)
{
	SCHOOL newSchool;

	menuAddAdditionalPrep(newSchool);

	ако(!addElement(schools, newSchool))
	{
		cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "Failed to create school: Name already exists!" << endl;
		върни;
	}

	menuDriver(dereferenceElement(schools, schools.begin() плюс(schools.size() минус 1)));
}

безтипов menuRemove(vector<SCHOOL> псевдоним schools)
{
	size_t choice;

	ако(schools.empty())
	{
		std::cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "There are currently no schools." << std::endl;
		върни;
	}

	listTable(schools);

	getMenuChoice(choice, schools.size());

	deleteElement(schools, choice минус 1);

	clearConsole();
}

безтипов menuRestore(vector<SCHOOL> псевдоним schools)
{
	низ choice;

	ако(!schools.empty())
	{
		cout << getAnsiEscape(ANSI_ESCAPE::FG_B_YELLOW)
			 << "WARNING: This operation will override your existing schools and you will not be able to recover them."
			 << endl
			 << getAnsiEscape(ANSI_ESCAPE::FG_YELLOW)
			 << "Do you wish to proceed? (y/n): " << getAnsiEscape(ANSI_ESCAPE::FG_B_YELLOW);

		getline(cin, choice);
		clearConsole();

		ако(choice[0] не_е_равно_на 'y' and choice[0] не_е_равно_на 'Y') върни;
	}

	restoreSchools(schools, "backup");
}

безтипов menuStore(константен vector<SCHOOL> псевдоним schools)
{
	низ choice;

	cout << getAnsiEscape(ANSI_ESCAPE::FG_B_YELLOW)
		 << "WARNING: This operation will override your existing backup and you will no longer be able to access it."
		 << endl
		 << getAnsiEscape(ANSI_ESCAPE::FG_YELLOW)
		 << "Do you wish to proceed? (y/n): " << getAnsiEscape(ANSI_ESCAPE::FG_B_YELLOW);

	getline(cin, choice);
	clearConsole();

	ако(choice[0] не_е_равно_на 'y' and choice[0] не_е_равно_на 'Y') върни;

	storeSchools(schools, "backup");
}

безтипов menuAddAdditionalPrep(SCHOOL псевдоним school)
{
	addElement(school.students, низ("INVALID"), {});
	addElement(school.teachers, низ("INVALID"), {});
	addElement(school.teams, 0ull, {"", "", "", {}, STATUS::ARCHIVED, "INVALID"});
	addElement(school.projects, низ("INVALID"), {"", "", {}, STATUS::ARCHIVED});
}

безтипов menuAddAdditionalPrep(TEAM псевдоним team)
{
	team.project е "INVALID";

	символ указател tempBuffer е нов символ[sizeof("YYYY-MM-DD")];
	time_t currTime;
	tm tm_;

	time(адрес_на currTime);

	// MS localtime_s
	localtime_s(адрес_на tm_, адрес_на currTime);

	strftime(tempBuffer, sizeof("YYYY-MM-DD"), "%F", адрес_на tm_);

	team.setupDate е tempBuffer;

	изтрий[] tempBuffer;
}

безтипов menuAddAdditionalPrep(TEAM_MEMBER псевдоним member)
{
	member.username е "INVALID";
}

безтипов menuRemoveAdditionalPrep(size_t key, константен TEAM псевдоним team, SCHOOL псевдоним parentSchool)
{
	vector<size_t>::iterator tempIt;

	за(авто it е parentSchool.teachers.begin(); it не_е_равно_на parentSchool.teachers.end(); it инкрементирай)
	{
		TEACHER псевдоним currTeacher е dereferenceElement(parentSchool.teachers, it);
		tempIt е find(currTeacher.teams.begin(), currTeacher.teams.end(), key);

		deleteElement(currTeacher.teams, tempIt минус currTeacher.teams.begin());
	}

	за(авто it е parentSchool.projects.begin(); it не_е_равно_на parentSchool.projects.end(); it инкрементирай)
	{
		PROJECT псевдоним currProject е dereferenceElement(parentSchool.projects, it);
		tempIt е find(currProject.teams.begin(), currProject.teams.end(), key);

		deleteElement(currProject.teams, tempIt минус currProject.teams.begin());
	}
}

безтипов menuRemoveAdditionalPrep(константен низ псевдоним key, константен PROJECT псевдоним project,
								  SCHOOL псевдоним parentSchool)
{
	за(авто it е parentSchool.teams.begin(); it не_е_равно_на parentSchool.teams.end(); it инкрементирай)
	{
		TEAM псевдоним currTeam е dereferenceElement(parentSchool.teams, it);

		ако(currTeam.project е_равно_на key) currTeam.project е "INVALID";
	}
}

безтипов menuRemoveAdditionalPrep(константен низ псевдоним key, константен STUDENT псевдоним student,
								  SCHOOL псевдоним parentSchool)
{
	vector<TEAM_MEMBER>::iterator tempIt;

	за(авто it е parentSchool.teams.begin(); it не_е_равно_на parentSchool.teams.end(); it инкрементирай)
	{
		TEAM псевдоним currTeam е dereferenceElement(parentSchool.teams, it);
		tempIt е find_if(
			currTeam.members.begin(),
			currTeam.members.end(),
			[псевдоним key](константен TEAM_MEMBER псевдоним currMember) { върни currMember.username е_равно_на key; });

		deleteElement(currTeam.members, tempIt минус currTeam.members.begin());
	}
}

безтипов menuEditCity(SCHOOL псевдоним school)
{
	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Current city: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN)
		 << school.city << endl;
	cout << getAnsiEscape(ANSI_ESCAPE::FG_YELLOW)
		 << "Enter new school city: " << getAnsiEscape(ANSI_ESCAPE::FG_B_YELLOW);
	getline(cin, school.city);

	clearConsole();
}

безтипов menuEditAddress(SCHOOL псевдоним school)
{
	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Current address: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN)
		 << school.address << endl;
	cout << getAnsiEscape(ANSI_ESCAPE::FG_YELLOW)
		 << "Enter new school address: " << getAnsiEscape(ANSI_ESCAPE::FG_B_YELLOW);
	getline(cin, school.address);

	clearConsole();
}

безтипов menuEditClass(STUDENT псевдоним student)
{
	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Current class: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN)
		 << student.grade << ' ' << student.classLetter << endl;
	cout << getAnsiEscape(ANSI_ESCAPE::FG_YELLOW) << "Enter new class: " << getAnsiEscape(ANSI_ESCAPE::FG_B_YELLOW);

	ако(!getStudentClass(student.grade, student.classLetter))
	{
		cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "Invalid input!" << endl;
		върни;
	}

	clearConsole();
}

булев_тип getStudentClass(беззнаков псевдоним grade, символ псевдоним classLetter)
{
	низ stemp;
	беззнаков utemp;
	символ ctemp;

	getline(cin, stemp);

	stringstream line(stemp);
	line.exceptions(ios::failbit | ios::badbit);

	пробвай
	{
		getUnsignedNumber(line, utemp, ' ', 12, 1);
		ако(line.str().empty()) върни грешно;
		getline(line, stemp);
		ctemp е stemp[0];
	}
	хвани(...)
	{
		върни грешно;
	}

	grade е utemp;
	classLetter е ctemp;

	върни вярно;
}

безтипов menuEditUsername(TEAM_MEMBER псевдоним member, константен SCHOOL псевдоним parentSchool)
{
	vector<константен низ указател> keys;

	size_t choice;

	ако(parentSchool.students.empty())
	{
		cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "No students!" << endl;
		върни;
	}

	listTable(parentSchool.students, parentSchool);

	keys.reserve(parentSchool.students.size());
	за(авто it е parentSchool.students.begin(); it не_е_равно_на parentSchool.students.end(); it инкрементирай)
	{
		ако(isValidKey(it->first)) keys.push_back(адрес_на it->first);
	}

	getMenuChoice(choice, parentSchool.students.size() минус 1);

	member.username е достъпи_стойността_на keys[choice минус 1];

	clearConsole();
}

безтипов menuEditRole(TEAM_MEMBER псевдоним member)
{
	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Legend:" << endl;
	за(int i е 0; i е_по_малко_или_равно_на 3; i инкрементирай)
	{
		cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << '(' << i << ") " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN)
			 << toString((TEAM_MEMBER::ROLE)i) << endl;
	}
	cout << endl;

	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Current role: " << (беззнаков)member.role << endl;
	cout << getAnsiEscape(ANSI_ESCAPE::FG_YELLOW) << "Enter new role: " << getAnsiEscape(ANSI_ESCAPE::FG_B_YELLOW);

	пробвай
	{
		getUnsignedNumber(cin, member.role, '\n', 3);
	}
	хвани(...)
	{
		clearConsole();
		cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "Invalid input!" << endl;
		върни;
	}

	clearConsole();
}

безтипов menuEditProject(TEAM псевдоним team, константен SCHOOL псевдоним parentSchool)
{
	vector<константен низ указател> keys;

	size_t choice;

	ако(parentSchool.projects.empty())
	{
		cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "No projects!" << endl;
		върни;
	}

	listTable(parentSchool.projects, parentSchool);

	keys.reserve(parentSchool.projects.size());
	за(авто it е parentSchool.projects.begin(); it не_е_равно_на parentSchool.projects.end(); it инкрементирай)
	{
		ако(isValidKey(it->first)) keys.push_back(адрес_на it->first);
	}

	getMenuChoice(choice, parentSchool.projects.size() минус 1);

	team.project е достъпи_стойността_на keys[choice минус 1];

	clearConsole();
}

булев_тип menuQueries(константен SCHOOL псевдоним school)
{
	size_t choice;
	vector<константен символ указател> options е{"Get teachers wihout teams", "Back to school"};

	printNewlines(1);

	displayMenuOptions(options);
	getMenuChoice(choice, options.size());

	clearConsole();

	превключвател(choice)
	{
		случай 1 : menuQueryTeachersWithoutTeam(school);
		break;
		случай 2 : върни грешно;
	}

	върни вярно;
}

безтипов menuQueryTeachersWithoutTeam(константен SCHOOL псевдоним school)
{
	vector<константен низ указател> keys;
	size_t choice;

	ако(school.projects.empty())
	{
		cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "No projects!" << endl;
		върни;
	}

	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Select project:" << endl;
	printNewlines(1);

	listTable(school.projects, school);

	keys.reserve(school.projects.size());
	за(авто it е school.projects.begin(); it не_е_равно_на school.projects.end(); it инкрементирай)
	{
		ако(isValidKey(it->first)) keys.push_back(адрес_на it->first);
	}

	getMenuChoice(choice, school.projects.size() минус 1);

	clearConsole();
	listTable(school.getTeachersWithoutTeam(достъпи_стойността_на keys[choice минус 1]), school.teachers, school);
}

безтипов displayDetails(константен STUDENT псевдоним student)
{
	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "First name: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN)
		 << student.firstName << endl
		 << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Last name: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN)
		 << student.lastName << endl
		 << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Email: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << student.email
		 << endl
		 << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Class: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << student.grade
		 << ' ' << student.classLetter << endl;

	cout << getAnsiEscape(ANSI_ESCAPE::RESET);
}

безтипов displayDetails(константен TEACHER псевдоним teacher)
{
	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "First name: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN)
		 << teacher.firstName << endl
		 << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Last name: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN)
		 << teacher.lastName << endl
		 << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Email: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << teacher.email
		 << endl
		 << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Number of assigned teams: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN)
		 << teacher.teams.size() << endl;

	cout << getAnsiEscape(ANSI_ESCAPE::RESET);
}

безтипов displayDetails(константен TEAM_MEMBER псевдоним member, константен SCHOOL псевдоним parentSchool)
{
	константен STUDENT псевдоним student е dereferenceElement(parentSchool.students, member.username);

	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Student: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN)
		 << student.firstName << ' ' << student.lastName << endl
		 << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Role: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN)
		 << toString(member.role) << endl;

	cout << getAnsiEscape(ANSI_ESCAPE::RESET);
}

безтипов displayDetails(константен TEAM псевдоним team, константен SCHOOL псевдоним parentSchool)
{
	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Name: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << team.name << endl
		 << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Setup date: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN)
		 << team.setupDate << endl
		 << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Description: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN)
		 << team.description << endl
		 << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Status: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN)
		 << toString(team.status) << endl
		 << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Project: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN)
		 << dereferenceElement(parentSchool.projects, team.project).name << endl;

	cout << getAnsiEscape(ANSI_ESCAPE::RESET);
}

безтипов displayDetails(константен PROJECT псевдоним project)
{
	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Name: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << project.name
		 << endl
		 << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Description: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN)
		 << project.description << endl
		 << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Status: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN)
		 << toString(project.status) << endl
		 << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Number of assigned teams: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN)
		 << project.teams.size() << endl;

	cout << getAnsiEscape(ANSI_ESCAPE::RESET);
}

безтипов displayDetails(константен SCHOOL псевдоним school)
{
	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Name: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << school.name
		 << endl
		 << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "City: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << school.city
		 << endl
		 << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Address: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << school.address
		 << endl
		 << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Number of students: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN)
		 << school.students.size() минус 1 << endl
		 << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Number of teachers: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN)
		 << school.teachers.size() минус 1 << endl
		 << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Number of teams: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN)
		 << school.teams.size() минус 1 << endl
		 << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << "Number of projects: " << getAnsiEscape(ANSI_ESCAPE::FG_GREEN)
		 << school.projects.size() минус 1 << endl;

	cout << getAnsiEscape(ANSI_ESCAPE::RESET);
}
