#include "console_io.h"
#include "data_manip.h"

#include <iomanip>

using namespace std;

void listTable(const vector<SCHOOL> &schools)
{
	ios initialState(nullptr);

	size_t colNoWidth, colNameWidth, colCityWidth, colAddressWidth, colStudentsWidth, colTeachersWidth, colTeamsWidth,
		colProjectsWidth;
	SCHOOL currSchool;
	string labelNo, labelName, labelCity, labelAddress, labelStudents, labelTeachers, labelTeams, labelProjects;

	if (schools.empty()) {
		cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "There are currently no schools." << endl;
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

	colNoWidth = max((size_t)ceil(log10(schools.size())), labelNo.size()) + 2;
	colNameWidth = labelName.size();
	colCityWidth = labelCity.size();
	colAddressWidth = labelAddress.size();
	colStudentsWidth = labelStudents.size() + 2;
	colTeachersWidth = labelTeachers.size() + 2;
	colTeamsWidth = labelTeams.size() + 2;
	colProjectsWidth = labelProjects.size() + 2;

	for (auto it = schools.begin(); it != schools.end(); it++) {
		currSchool = dereferenceElement(schools, it);

		colNameWidth = max(colNameWidth, currSchool.name.size());
		colCityWidth = max(colCityWidth, currSchool.city.size());
		colAddressWidth = max(colAddressWidth, currSchool.address.size());
	}

	colNameWidth += 2;
	colCityWidth += 2;
	colAddressWidth += 2;

	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << left << setw(colNoWidth) << labelNo << setw(colNameWidth)
		 << labelName << setw(colCityWidth) << labelCity << setw(colAddressWidth) << labelAddress
		 << setw(colStudentsWidth) << labelStudents << setw(colTeachersWidth) << labelTeachers << setw(colTeamsWidth)
		 << labelTeams << setw(colProjectsWidth) << labelProjects << endl;

	cout << string(colNoWidth + colNameWidth + colCityWidth + colAddressWidth + colStudentsWidth + colTeachersWidth +
					   colTeamsWidth + colProjectsWidth,
				   '-')
		 << endl;

	for (size_t i = 0; i < schools.size(); i++) {
		const SCHOOL &currSchool = dereferenceElement(schools, schools.begin() + i);

		cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << left << setw(colNoWidth) << i + 1
			 << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << setw(colNameWidth) << currSchool.name << setw(colCityWidth)
			 << currSchool.city << setw(colAddressWidth) << currSchool.address << setw(colStudentsWidth)
			 << currSchool.students.size() - 1 << setw(colTeachersWidth) << currSchool.teachers.size() - 1
			 << setw(colTeamsWidth) << currSchool.teams.size() - 1 << setw(colProjectsWidth)
			 << currSchool.projects.size() - 1 << endl;
	}

	cout.copyfmt(initialState);
	cout << getAnsiEscape(ANSI_ESCAPE::RESET);
}

void listTable(const unordered_map<string, STUDENT> &students, const SCHOOL &parentSchool)
{
	ios initialState(nullptr);

	size_t colNoWidth, colFirstNameWidth, colLastNameWidth, colEmailWidth, colClassWidth;
	size_t loopCounter;
	string labelNo, labelFirstName, labelLastName, labelEmail, labelClass;

	if (!hasValidRecords(students)) {
		cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "There are currently no students." << endl;
		return;
	}

	initialState.copyfmt(cout);

	labelNo = "No.";
	labelFirstName = "First name";
	labelLastName = "Last name";
	labelEmail = "Email";
	labelClass = "Class";

	colNoWidth = max((size_t)ceil(log10(students.size())), labelNo.size()) + 2;
	colFirstNameWidth = labelFirstName.size();
	colLastNameWidth = labelLastName.size();
	colEmailWidth = labelEmail.size();
	colClassWidth = labelClass.size() + 2;

	for (auto it = students.begin(); it != students.end(); it++) {
		const STUDENT &currStudent = dereferenceElement(students, it);

		colFirstNameWidth = max(colFirstNameWidth, currStudent.firstName.size());
		colLastNameWidth = max(colLastNameWidth, currStudent.lastName.size());
		colEmailWidth = max(colEmailWidth, currStudent.email.size());
	}

	colFirstNameWidth += 2;
	colLastNameWidth += 2;
	colEmailWidth += 2;

	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << left << setw(colNoWidth) << labelNo << setw(colFirstNameWidth)
		 << labelFirstName << setw(colLastNameWidth) << labelLastName << setw(colEmailWidth) << labelEmail
		 << setw(colClassWidth) << labelClass << endl;

	cout << string(colNoWidth + colFirstNameWidth + colLastNameWidth + colEmailWidth + colClassWidth, '-') << endl;

	loopCounter = 0;
	for (auto it = students.begin(); it != students.end(); it++) {
		if (!isValidKey(it->first)) continue;

		loopCounter++;
		const STUDENT &currStudent = dereferenceElement(students, it);

		cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << left << setw(colNoWidth) << loopCounter
			 << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << setw(colFirstNameWidth) << currStudent.firstName
			 << setw(colLastNameWidth) << currStudent.lastName << setw(colEmailWidth) << currStudent.email
			 << currStudent.grade << ' ' << currStudent.classLetter << endl;
	}

	cout.copyfmt(initialState);
	cout << getAnsiEscape(ANSI_ESCAPE::RESET);
}

void listTable(const unordered_map<string, TEACHER> &teachers, const SCHOOL &parentSchool)
{
	ios initialState(nullptr);

	size_t colNoWidth, colFirstNameWidth, colLastNameWidth, colEmailWidth, colTeamsWidth;
	size_t loopCounter;
	string labelNo, labelFirstName, labelLastName, labelEmail, labelTeams;

	if (!hasValidRecords(teachers)) {
		cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "There are currently no teachers." << endl;
		return;
	}

	initialState.copyfmt(cout);

	labelNo = "No.";
	labelFirstName = "First name";
	labelLastName = "Last name";
	labelEmail = "Email";
	labelTeams = "Assigned teams";

	colNoWidth = max((size_t)ceil(log10(teachers.size())), labelNo.size()) + 2;
	colFirstNameWidth = labelFirstName.size();
	colLastNameWidth = labelLastName.size();
	colEmailWidth = labelEmail.size();
	colTeamsWidth = labelTeams.size() + 2;

	for (auto it = teachers.begin(); it != teachers.end(); it++) {
		const TEACHER &currTeacher = dereferenceElement(teachers, it);

		colFirstNameWidth = max(colFirstNameWidth, currTeacher.firstName.size());
		colLastNameWidth = max(colLastNameWidth, currTeacher.lastName.size());
		colEmailWidth = max(colEmailWidth, currTeacher.email.size());
	}

	colFirstNameWidth += 2;
	colLastNameWidth += 2;
	colEmailWidth += 2;

	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << left << setw(colNoWidth) << labelNo << setw(colFirstNameWidth)
		 << labelFirstName << setw(colLastNameWidth) << labelLastName << setw(colEmailWidth) << labelEmail
		 << setw(colTeamsWidth) << labelTeams << endl;

	cout << string(colNoWidth + colFirstNameWidth + colLastNameWidth + colEmailWidth + colTeamsWidth, '-') << endl;

	loopCounter = 0;
	for (auto it = teachers.begin(); it != teachers.end(); it++) {
		if (!isValidKey(it->first)) continue;

		loopCounter++;
		const TEACHER &currTeacher = dereferenceElement(teachers, it);

		cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << left << setw(colNoWidth) << loopCounter
			 << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << setw(colFirstNameWidth) << currTeacher.firstName
			 << setw(colLastNameWidth) << currTeacher.lastName << setw(colEmailWidth) << currTeacher.email
			 << setw(colTeamsWidth) << currTeacher.teams.size() << endl;
	}

	cout.copyfmt(initialState);
	cout << getAnsiEscape(ANSI_ESCAPE::RESET);
}

void listTable(const unordered_map<size_t, TEAM> &teams, const SCHOOL &parentSchool)
{
	ios initialState(nullptr);

	size_t colNoWidth, colNameWidth, colProjectWidth, colDateWidth, colMembersWidth, colStatusWidth;
	size_t loopCounter;
	string labelNo, labelName, labelProject, labelDate, labelMembers, labelStatus;

	if (!hasValidRecords(teams)) {
		cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "There are currently no teams." << endl;
		return;
	}

	initialState.copyfmt(cout);

	labelNo = "No.";
	labelName = "Name";
	labelProject = "Project";
	labelDate = "Setup date";
	labelMembers = "Members";
	labelStatus = "Status";

	colNoWidth = max((size_t)ceil(log10(teams.size())), labelNo.size()) + 2;
	colNameWidth = labelName.size();
	colProjectWidth = labelProject.size();
	colDateWidth = max(10ull + 2, labelDate.size());
	colMembersWidth = labelMembers.size() + 2;
	colStatusWidth = labelStatus.size();

	for (auto it = teams.begin(); it != teams.end(); it++) {
		const TEAM &currTeam = dereferenceElement(teams, it);

		colNameWidth = max(colNameWidth, currTeam.name.size());
		colProjectWidth = max(colProjectWidth, dereferenceElement(parentSchool.projects, currTeam.project).name.size());
		colStatusWidth = max(colStatusWidth, toString(currTeam.status).size());
	}

	colNameWidth += 2;
	colProjectWidth += 2;
	colStatusWidth += 2;

	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << left << setw(colNoWidth) << labelNo << setw(colNameWidth)
		 << labelName << setw(colProjectWidth) << labelProject << setw(colDateWidth) << labelDate
		 << setw(colMembersWidth) << labelMembers << setw(colStatusWidth) << labelStatus << endl;

	cout << string(colNoWidth + colNameWidth + colProjectWidth + colDateWidth + colMembersWidth + colStatusWidth, '-')
		 << endl;

	loopCounter = 0;
	for (auto it = teams.begin(); it != teams.end(); it++) {
		if (!isValidKey(it->first)) continue;

		loopCounter++;
		const TEAM &currTeam = dereferenceElement(teams, it);

		cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << left << setw(colNoWidth) << loopCounter
			 << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << setw(colNameWidth) << currTeam.name << setw(colProjectWidth)
			 << dereferenceElement(parentSchool.projects, currTeam.project).name << setw(colDateWidth)
			 << currTeam.setupDate << setw(colMembersWidth) << currTeam.members.size() << setw(colStatusWidth)
			 << toString(currTeam.status) << endl;
	}

	cout.copyfmt(initialState);
	cout << getAnsiEscape(ANSI_ESCAPE::RESET);
}

void listTable(const unordered_map<string, PROJECT> &projects, const SCHOOL &parentSchool)
{
	ios initialState(nullptr);

	size_t colNoWidth, colNameWidth, colTeamsWidth, colStatusWidth;
	size_t loopCounter;
	string labelNo, labelName, labelTeams, labelStatus;

	if (!hasValidRecords(projects)) {
		cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "There are currently no projects." << endl;
		return;
	}

	initialState.copyfmt(cout);

	labelNo = "No.";
	labelName = "Name";
	labelTeams = "Teams";
	labelStatus = "Status";

	colNoWidth = max((size_t)ceil(log10(projects.size())), labelNo.size()) + 2;
	colNameWidth = labelName.size();
	colTeamsWidth = labelTeams.size() + 2;
	colStatusWidth = labelStatus.size();

	for (auto it = projects.begin(); it != projects.end(); it++) {
		const PROJECT &currProject = dereferenceElement(projects, it);

		colNameWidth = max(colNameWidth, currProject.name.size());
		colStatusWidth = max(colStatusWidth, toString(currProject.status).size());
	}

	colNameWidth += 2;
	colStatusWidth += 2;

	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << left << setw(colNoWidth) << labelNo << setw(colNameWidth)
		 << labelName << setw(colTeamsWidth) << labelTeams << setw(colStatusWidth) << labelStatus << endl;

	cout << string(colNoWidth + colNameWidth + colTeamsWidth + colStatusWidth, '-') << endl;

	loopCounter = 0;
	for (auto it = projects.begin(); it != projects.end(); it++) {
		if (!isValidKey(it->first)) continue;

		loopCounter++;
		const PROJECT &currProject = dereferenceElement(projects, it);

		cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << left << setw(colNoWidth) << loopCounter
			 << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << setw(colNameWidth) << currProject.name << setw(colTeamsWidth)
			 << currProject.teams.size() << setw(colStatusWidth) << toString(currProject.status) << endl;
	}

	cout.copyfmt(initialState);
	cout << getAnsiEscape(ANSI_ESCAPE::RESET);
}

void listTable(const vector<TEAM_MEMBER> &members, const SCHOOL &parentSchool)
{
	ios initialState(nullptr);

	size_t colNoWidth, colFirstNameWidth, colLastNameWidth, colEmailWidth, colClassWidth, colRoleWidth;
	size_t loopCounter;
	string labelNo, labelFirstName, labelLastName, labelEmail, labelClass, labelRole;

	if (members.empty()) {
		cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "There are currently no students." << endl;
		return;
	}

	initialState.copyfmt(cout);

	labelNo = "No.";
	labelFirstName = "First name";
	labelLastName = "Last name";
	labelEmail = "Email";
	labelClass = "Class";
	labelRole = "Role";

	colNoWidth = max((size_t)ceil(log10(members.size())), labelNo.size()) + 2;
	colFirstNameWidth = labelFirstName.size();
	colLastNameWidth = labelLastName.size();
	colEmailWidth = labelEmail.size();
	colClassWidth = labelClass.size() + 2;
	colRoleWidth = labelRole.size();

	for (auto it = members.begin(); it != members.end(); it++) {
		const TEAM_MEMBER &currMember = dereferenceElement(members, it);

		colFirstNameWidth =
			max(colFirstNameWidth, dereferenceElement(parentSchool.students, currMember.username).firstName.size());
		colLastNameWidth =
			max(colLastNameWidth, dereferenceElement(parentSchool.students, currMember.username).lastName.size());
		colEmailWidth = max(colEmailWidth, dereferenceElement(parentSchool.students, currMember.username).email.size());
		colRoleWidth = max(colRoleWidth, toString(currMember.role).size());
	}

	colFirstNameWidth += 2;
	colLastNameWidth += 2;
	colEmailWidth += 2;
	colRoleWidth += 2;

	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << left << setw(colNoWidth) << labelNo << setw(colFirstNameWidth)
		 << labelFirstName << setw(colLastNameWidth) << labelLastName << setw(colEmailWidth) << labelEmail
		 << setw(colClassWidth) << labelClass << setw(colRoleWidth) << labelRole << endl;

	cout << string(colNoWidth + colFirstNameWidth + colLastNameWidth + colEmailWidth + colClassWidth + colRoleWidth,
				   '-')
		 << endl;

	loopCounter = 0;
	for (auto it = members.begin(); it != members.end(); it++) {
		loopCounter++;
		const TEAM_MEMBER &currMember = dereferenceElement(members, it);

		cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << left << setw(colNoWidth) << loopCounter
			 << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << setw(colFirstNameWidth)
			 << dereferenceElement(parentSchool.students, currMember.username).firstName << setw(colLastNameWidth)
			 << dereferenceElement(parentSchool.students, currMember.username).lastName << setw(colEmailWidth)
			 << dereferenceElement(parentSchool.students, currMember.username).email << right << setw(colClassWidth - 4)
			 << dereferenceElement(parentSchool.students, currMember.username).grade << left << ' ' << setw(3)
			 << dereferenceElement(parentSchool.students, currMember.username).classLetter << setw(colRoleWidth)
			 << toString(currMember.role) << endl;
	}

	cout.copyfmt(initialState);
	cout << getAnsiEscape(ANSI_ESCAPE::RESET);
}

void listTable(const vector<size_t> &keys, const unordered_map<size_t, TEAM> &teams, const SCHOOL &parentSchool)
{
	ios initialState(nullptr);

	size_t colNoWidth, colNameWidth, colProjectWidth, colDateWidth, colMembersWidth, colStatusWidth;
	size_t loopCounter;
	string labelNo, labelName, labelProject, labelDate, labelMembers, labelStatus;

	if (keys.empty()) {
		cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "There are currently no teams." << endl;
		return;
	}

	initialState.copyfmt(cout);

	labelNo = "No.";
	labelName = "Name";
	labelProject = "Project";
	labelDate = "Setup date";
	labelMembers = "Members";
	labelStatus = "Status";

	colNoWidth = max((size_t)ceil(log10(keys.size())), labelNo.size()) + 2;
	colNameWidth = labelName.size();
	colProjectWidth = labelProject.size();
	colDateWidth = max(10ull + 2, labelDate.size());
	colMembersWidth = labelMembers.size() + 2;
	colStatusWidth = labelStatus.size();

	for (auto it = keys.begin(); it != keys.end(); it++) {
		const TEAM &currTeam = dereferenceElement(teams, *it);

		colNameWidth = max(colNameWidth, currTeam.name.size());
		colProjectWidth = max(colProjectWidth, dereferenceElement(parentSchool.projects, currTeam.project).name.size());
		colStatusWidth = max(colStatusWidth, toString(currTeam.status).size());
	}

	colNameWidth += 2;
	colProjectWidth += 2;
	colStatusWidth += 2;

	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << left << setw(colNoWidth) << labelNo << setw(colNameWidth)
		 << labelName << setw(colProjectWidth) << labelProject << setw(colDateWidth) << labelDate
		 << setw(colMembersWidth) << labelMembers << setw(colStatusWidth) << labelStatus << endl;

	cout << string(colNoWidth + colNameWidth + colProjectWidth + colDateWidth + colMembersWidth + colStatusWidth, '-')
		 << endl;

	loopCounter = 0;
	for (auto it = keys.begin(); it != keys.end(); it++) {
		loopCounter++;
		const TEAM &currTeam = dereferenceElement(teams, *it);

		cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << left << setw(colNoWidth) << loopCounter
			 << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << setw(colNameWidth) << currTeam.name << setw(colProjectWidth)
			 << dereferenceElement(parentSchool.projects, currTeam.project).name << setw(colDateWidth)
			 << currTeam.setupDate << setw(colMembersWidth) << currTeam.members.size() << setw(colStatusWidth)
			 << toString(currTeam.status) << endl;
	}

	cout.copyfmt(initialState);
	cout << getAnsiEscape(ANSI_ESCAPE::RESET);
}

void listTable(const vector<string> &keys, const unordered_map<string, TEACHER> &teachers, const SCHOOL &parentSchool)
{
	ios initialState(nullptr);

	size_t colNoWidth, colFirstNameWidth, colLastNameWidth, colEmailWidth, colTeamsWidth;
	size_t loopCounter;
	string labelNo, labelFirstName, labelLastName, labelEmail, labelTeams;

	if (teachers.empty()) {
		cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "There are currently no teachers." << endl;
		return;
	}

	initialState.copyfmt(cout);

	labelNo = "No.";
	labelFirstName = "First name";
	labelLastName = "Last name";
	labelEmail = "Email";
	labelTeams = "Assigned teams";

	colNoWidth = max((size_t)ceil(log10(teachers.size())), labelNo.size()) + 2;
	colFirstNameWidth = labelFirstName.size();
	colLastNameWidth = labelLastName.size();
	colEmailWidth = labelEmail.size();
	colTeamsWidth = labelTeams.size() + 2;

	for (auto it = keys.begin(); it != keys.end(); it++) {
		const TEACHER &currTeacher = dereferenceElement(teachers, *it);

		colFirstNameWidth = max(colFirstNameWidth, currTeacher.firstName.size());
		colLastNameWidth = max(colLastNameWidth, currTeacher.lastName.size());
		colEmailWidth = max(colEmailWidth, currTeacher.email.size());
	}

	colFirstNameWidth += 2;
	colLastNameWidth += 2;
	colEmailWidth += 2;

	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << left << setw(colNoWidth) << labelNo << setw(colFirstNameWidth)
		 << labelFirstName << setw(colLastNameWidth) << labelLastName << setw(colEmailWidth) << labelEmail
		 << setw(colTeamsWidth) << labelTeams << endl;

	cout << string(colNoWidth + colFirstNameWidth + colLastNameWidth + colEmailWidth + colTeamsWidth, '-') << endl;

	loopCounter = 0;
	for (auto it = keys.begin(); it != keys.end(); it++) {
		loopCounter++;
		const TEACHER &currTeacher = dereferenceElement(teachers, *it);

		cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << left << setw(colNoWidth) << loopCounter
			 << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << setw(colFirstNameWidth) << currTeacher.firstName
			 << setw(colLastNameWidth) << currTeacher.lastName << setw(colEmailWidth) << currTeacher.email
			 << setw(colTeamsWidth) << currTeacher.teams.size() << endl;
	}

	cout.copyfmt(initialState);
	cout << getAnsiEscape(ANSI_ESCAPE::RESET);
}
