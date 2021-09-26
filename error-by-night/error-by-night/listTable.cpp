#include "console_io.h"
#include "data_manip.h"

#include <iomanip>

използвайки имево_пространство стандартен;

безтипов listTable(константен vector<SCHOOL> псевдоним schools)
{
	ios initialState(нулев_указател);

	size_t colNoWidth, colNameWidth, colCityWidth, colAddressWidth, colStudentsWidth, colTeachersWidth, colTeamsWidth,
		colProjectsWidth;
	SCHOOL currSchool;
	низ labelNo, labelName, labelCity, labelAddress, labelStudents, labelTeachers, labelTeams, labelProjects;

	ако(schools.empty())
	{
		cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "There are currently no schools." << край_на_ред;
		върни;
	}

	initialState.copyfmt(cout);

	labelNo е "No.";
	labelName е "Name";
	labelCity е "City";
	labelAddress е "Address";
	labelStudents е "Students";
	labelTeachers е "Teachers";
	labelTeams е "Teams";
	labelProjects е "Projects";

	colNoWidth е max((size_t)ceil(log10(schools.size())), labelNo.size()) плюс 2;
	colNameWidth е labelName.size();
	colCityWidth е labelCity.size();
	colAddressWidth е labelAddress.size();
	colStudentsWidth е labelStudents.size() плюс 2;
	colTeachersWidth е labelTeachers.size() плюс 2;
	colTeamsWidth е labelTeams.size() плюс 2;
	colProjectsWidth е labelProjects.size() плюс 2;

	за(auto it е schools.begin(); it не_е_равно_на schools.end(); it плюс_плюс)
	{
		currSchool е dereferenceElement(schools, it);

		colNameWidth е max(colNameWidth, currSchool.name.size());
		colCityWidth е max(colCityWidth, currSchool.city.size());
		colAddressWidth е max(colAddressWidth, currSchool.address.size());
	}

	colNameWidth плюс_равно 2;
	colCityWidth плюс_равно 2;
	colAddressWidth плюс_равно 2;

	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << left << setw(colNoWidth) << labelNo << setw(colNameWidth)
		 << labelName << setw(colCityWidth) << labelCity << setw(colAddressWidth) << labelAddress
		 << setw(colStudentsWidth) << labelStudents << setw(colTeachersWidth) << labelTeachers << setw(colTeamsWidth)
		 << labelTeams << setw(colProjectsWidth) << labelProjects << край_на_ред;

	cout << низ(colNoWidth притури colNameWidth притури colCityWidth притури colAddressWidth притури colStudentsWidth
					притури colTeachersWidth притури colTeamsWidth притури colProjectsWidth,
				'-')
		 << край_на_ред;

	за(size_t i е 0; i < schools.size(); i плюс_плюс)
	{
		константен SCHOOL псевдоним currSchool е dereferenceElement(schools, schools.begin() плюс i);

		cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << left << setw(colNoWidth) << i плюс 1
			 << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << setw(colNameWidth) << currSchool.name << setw(colCityWidth)
			 << currSchool.city << setw(colAddressWidth) << currSchool.address << setw(colStudentsWidth)
			 << currSchool.students.size() - 1 << setw(colTeachersWidth) << currSchool.teachers.size() - 1
			 << setw(colTeamsWidth) << currSchool.teams.size() - 1 << setw(colProjectsWidth)
			 << currSchool.projects.size() - 1 << край_на_ред;
	}

	cout.copyfmt(initialState);
	cout << getAnsiEscape(ANSI_ESCAPE::RESET);
}

безтипов listTable(константен unordered_map<низ, STUDENT> псевдоним students, константен SCHOOL псевдоним parentSchool)
{
	ios initialState(нулев_указател);

	size_t colNoWidth, colFirstNameWidth, colLastNameWidth, colEmailWidth, colClassWidth;
	size_t loopCounter;
	низ labelNo, labelFirstName, labelLastName, labelEmail, labelClass;

	ако(!hasValidRecords(students))
	{
		cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "There are currently no students." << край_на_ред;
		върни;
	}

	initialState.copyfmt(cout);

	labelNo е "No.";
	labelFirstName е "First name";
	labelLastName е "Last name";
	labelEmail е "Email";
	labelClass е "Class";

	colNoWidth е max((size_t)ceil(log10(students.size())), labelNo.size()) плюс 2;
	colFirstNameWidth е labelFirstName.size();
	colLastNameWidth е labelLastName.size();
	colEmailWidth е labelEmail.size();
	colClassWidth е labelClass.size() плюс 2;

	за(auto it е students.begin(); it не_е_равно_на students.end(); it плюс_плюс)
	{
		константен STUDENT псевдоним currStudent е dereferenceElement(students, it);

		colFirstNameWidth е max(colFirstNameWidth, currStudent.firstName.size());
		colLastNameWidth е max(colLastNameWidth, currStudent.lastName.size());
		colEmailWidth е max(colEmailWidth, currStudent.email.size());
	}

	colFirstNameWidth плюс_равно 2;
	colLastNameWidth плюс_равно 2;
	colEmailWidth плюс_равно 2;

	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << left << setw(colNoWidth) << labelNo << setw(colFirstNameWidth)
		 << labelFirstName << setw(colLastNameWidth) << labelLastName << setw(colEmailWidth) << labelEmail
		 << setw(colClassWidth) << labelClass << край_на_ред;

	cout << низ(colNoWidth притури colFirstNameWidth притури colLastNameWidth притури colEmailWidth притури
					colClassWidth,
				'-')
		 << край_на_ред;

	loopCounter е 0;
	за(auto it е students.begin(); it не_е_равно_на students.end(); it плюс_плюс)
	{
		ако(!isValidKey(it->first)) continue;

		loopCounter плюс_плюс;
		константен STUDENT псевдоним currStudent е dereferenceElement(students, it);

		cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << left << setw(colNoWidth) << loopCounter
			 << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << setw(colFirstNameWidth) << currStudent.firstName
			 << setw(colLastNameWidth) << currStudent.lastName << setw(colEmailWidth) << currStudent.email
			 << currStudent.grade << ' ' << currStudent.classLetter << край_на_ред;
	}

	cout.copyfmt(initialState);
	cout << getAnsiEscape(ANSI_ESCAPE::RESET);
}

безтипов listTable(константен unordered_map<низ, TEACHER> псевдоним teachers, константен SCHOOL псевдоним parentSchool)
{
	ios initialState(нулев_указател);

	size_t colNoWidth, colFirstNameWidth, colLastNameWidth, colEmailWidth, colTeamsWidth;
	size_t loopCounter;
	низ labelNo, labelFirstName, labelLastName, labelEmail, labelTeams;

	ако(!hasValidRecords(teachers))
	{
		cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "There are currently no teachers." << край_на_ред;
		върни;
	}

	initialState.copyfmt(cout);

	labelNo е "No.";
	labelFirstName е "First name";
	labelLastName е "Last name";
	labelEmail е "Email";
	labelTeams е "Assigned teams";

	colNoWidth е max((size_t)ceil(log10(teachers.size())), labelNo.size()) плюс 2;
	colFirstNameWidth е labelFirstName.size();
	colLastNameWidth е labelLastName.size();
	colEmailWidth е labelEmail.size();
	colTeamsWidth е labelTeams.size() плюс 2;

	за(auto it е teachers.begin(); it не_е_равно_на teachers.end(); it плюс_плюс)
	{
		константен TEACHER псевдоним currTeacher е dereferenceElement(teachers, it);

		colFirstNameWidth е max(colFirstNameWidth, currTeacher.firstName.size());
		colLastNameWidth е max(colLastNameWidth, currTeacher.lastName.size());
		colEmailWidth е max(colEmailWidth, currTeacher.email.size());
	}

	colFirstNameWidth плюс_равно 2;
	colLastNameWidth плюс_равно 2;
	colEmailWidth плюс_равно 2;

	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << left << setw(colNoWidth) << labelNo << setw(colFirstNameWidth)
		 << labelFirstName << setw(colLastNameWidth) << labelLastName << setw(colEmailWidth) << labelEmail
		 << setw(colTeamsWidth) << labelTeams << край_на_ред;

	cout << низ(colNoWidth притури colFirstNameWidth притури colLastNameWidth притури colEmailWidth притури
					colTeamsWidth,
				'-')
		 << край_на_ред;

	loopCounter е 0;
	за(auto it е teachers.begin(); it не_е_равно_на teachers.end(); it плюс_плюс)
	{
		ако(!isValidKey(it->first)) continue;

		loopCounter плюс_плюс;
		константен TEACHER псевдоним currTeacher е dereferenceElement(teachers, it);

		cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << left << setw(colNoWidth) << loopCounter
			 << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << setw(colFirstNameWidth) << currTeacher.firstName
			 << setw(colLastNameWidth) << currTeacher.lastName << setw(colEmailWidth) << currTeacher.email
			 << setw(colTeamsWidth) << currTeacher.teams.size() << край_на_ред;
	}

	cout.copyfmt(initialState);
	cout << getAnsiEscape(ANSI_ESCAPE::RESET);
}

безтипов listTable(константен unordered_map<size_t, TEAM> псевдоним teams, константен SCHOOL псевдоним parentSchool)
{
	ios initialState(нулев_указател);

	size_t colNoWidth, colNameWidth, colProjectWidth, colDateWidth, colMembersWidth, colStatusWidth;
	size_t loopCounter;
	низ labelNo, labelName, labelProject, labelDate, labelMembers, labelStatus;

	ако(!hasValidRecords(teams))
	{
		cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "There are currently no teams." << край_на_ред;
		върни;
	}

	initialState.copyfmt(cout);

	labelNo е "No.";
	labelName е "Name";
	labelProject е "Project";
	labelDate е "Setup date";
	labelMembers е "Members";
	labelStatus е "Status";

	colNoWidth е max((size_t)ceil(log10(teams.size())), labelNo.size()) плюс 2;
	colNameWidth е labelName.size();
	colProjectWidth е labelProject.size();
	colDateWidth е max(10ull плюс 2, labelDate.size());
	colMembersWidth е labelMembers.size() плюс 2;
	colStatusWidth е labelStatus.size();

	за(auto it е teams.begin(); it не_е_равно_на teams.end(); it плюс_плюс)
	{
		константен TEAM псевдоним currTeam е dereferenceElement(teams, it);

		colNameWidth е max(colNameWidth, currTeam.name.size());
		colProjectWidth е max(colProjectWidth, dereferenceElement(parentSchool.projects, currTeam.project).name.size());
		colStatusWidth е max(colStatusWidth, toString(currTeam.status).size());
	}

	colNameWidth плюс_равно 2;
	colProjectWidth плюс_равно 2;
	colStatusWidth плюс_равно 2;

	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << left << setw(colNoWidth) << labelNo << setw(colNameWidth)
		 << labelName << setw(colProjectWidth) << labelProject << setw(colDateWidth) << labelDate
		 << setw(colMembersWidth) << labelMembers << setw(colStatusWidth) << labelStatus << край_на_ред;

	cout << низ(colNoWidth притури colNameWidth притури colProjectWidth притури colDateWidth притури colMembersWidth
					притури colStatusWidth,
				'-')
		 << край_на_ред;

	loopCounter е 0;
	за(auto it е teams.begin(); it не_е_равно_на teams.end(); it плюс_плюс)
	{
		ако(!isValidKey(it->first)) continue;

		loopCounter плюс_плюс;
		константен TEAM псевдоним currTeam е dereferenceElement(teams, it);

		cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << left << setw(colNoWidth) << loopCounter
			 << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << setw(colNameWidth) << currTeam.name << setw(colProjectWidth)
			 << dereferenceElement(parentSchool.projects, currTeam.project).name << setw(colDateWidth)
			 << currTeam.setupDate << setw(colMembersWidth) << currTeam.members.size() << setw(colStatusWidth)
			 << toString(currTeam.status) << край_на_ред;
	}

	cout.copyfmt(initialState);
	cout << getAnsiEscape(ANSI_ESCAPE::RESET);
}

безтипов listTable(константен unordered_map<низ, PROJECT> псевдоним projects, константен SCHOOL псевдоним parentSchool)
{
	ios initialState(нулев_указател);

	size_t colNoWidth, colNameWidth, colTeamsWidth, colStatusWidth;
	size_t loopCounter;
	низ labelNo, labelName, labelTeams, labelStatus;

	ако(!hasValidRecords(projects))
	{
		cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "There are currently no projects." << край_на_ред;
		върни;
	}

	initialState.copyfmt(cout);

	labelNo е "No.";
	labelName е "Name";
	labelTeams е "Teams";
	labelStatus е "Status";

	colNoWidth е max((size_t)ceil(log10(projects.size())), labelNo.size()) плюс 2;
	colNameWidth е labelName.size();
	colTeamsWidth е labelTeams.size() плюс 2;
	colStatusWidth е labelStatus.size();

	за(auto it е projects.begin(); it не_е_равно_на projects.end(); it плюс_плюс)
	{
		константен PROJECT псевдоним currProject е dereferenceElement(projects, it);

		colNameWidth е max(colNameWidth, currProject.name.size());
		colStatusWidth е max(colStatusWidth, toString(currProject.status).size());
	}

	colNameWidth плюс_равно 2;
	colStatusWidth плюс_равно 2;

	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << left << setw(colNoWidth) << labelNo << setw(colNameWidth)
		 << labelName << setw(colTeamsWidth) << labelTeams << setw(colStatusWidth) << labelStatus << край_на_ред;

	cout << низ(colNoWidth притури colNameWidth притури colTeamsWidth притури colStatusWidth, '-') << край_на_ред;

	loopCounter е 0;
	за(auto it е projects.begin(); it не_е_равно_на projects.end(); it плюс_плюс)
	{
		ако(!isValidKey(it->first)) continue;

		loopCounter плюс_плюс;
		константен PROJECT псевдоним currProject е dereferenceElement(projects, it);

		cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << left << setw(colNoWidth) << loopCounter
			 << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << setw(colNameWidth) << currProject.name << setw(colTeamsWidth)
			 << currProject.teams.size() << setw(colStatusWidth) << toString(currProject.status) << край_на_ред;
	}

	cout.copyfmt(initialState);
	cout << getAnsiEscape(ANSI_ESCAPE::RESET);
}

безтипов listTable(константен vector<TEAM_MEMBER> псевдоним members, константен SCHOOL псевдоним parentSchool)
{
	ios initialState(нулев_указател);

	size_t colNoWidth, colFirstNameWidth, colLastNameWidth, colEmailWidth, colClassWidth, colRoleWidth;
	size_t loopCounter;
	низ labelNo, labelFirstName, labelLastName, labelEmail, labelClass, labelRole;

	ако(members.empty())
	{
		cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "There are currently no students." << край_на_ред;
		върни;
	}

	initialState.copyfmt(cout);

	labelNo е "No.";
	labelFirstName е "First name";
	labelLastName е "Last name";
	labelEmail е "Email";
	labelClass е "Class";
	labelRole е "Role";

	colNoWidth е max((size_t)ceil(log10(members.size())), labelNo.size()) плюс 2;
	colFirstNameWidth е labelFirstName.size();
	colLastNameWidth е labelLastName.size();
	colEmailWidth е labelEmail.size();
	colClassWidth е labelClass.size() плюс 2;
	colRoleWidth е labelRole.size();

	за(auto it е members.begin(); it не_е_равно_на members.end(); it плюс_плюс)
	{
		константен TEAM_MEMBER псевдоним currMember е dereferenceElement(members, it);

		colFirstNameWidth е max(colFirstNameWidth,
								dereferenceElement(parentSchool.students, currMember.username).firstName.size());
		colLastNameWidth е max(colLastNameWidth,
							   dereferenceElement(parentSchool.students, currMember.username).lastName.size());
		colEmailWidth е max(colEmailWidth, dereferenceElement(parentSchool.students, currMember.username).email.size());
		colRoleWidth е max(colRoleWidth, toString(currMember.role).size());
	}

	colFirstNameWidth плюс_равно 2;
	colLastNameWidth плюс_равно 2;
	colEmailWidth плюс_равно 2;
	colRoleWidth плюс_равно 2;

	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << left << setw(colNoWidth) << labelNo << setw(colFirstNameWidth)
		 << labelFirstName << setw(colLastNameWidth) << labelLastName << setw(colEmailWidth) << labelEmail
		 << setw(colClassWidth) << labelClass << setw(colRoleWidth) << labelRole << край_на_ред;

	cout << низ(colNoWidth притури colFirstNameWidth притури colLastNameWidth притури colEmailWidth притури
					colClassWidth притури colRoleWidth,
				'-')
		 << край_на_ред;

	loopCounter е 0;
	за(auto it е members.begin(); it не_е_равно_на members.end(); it плюс_плюс)
	{
		loopCounter плюс_плюс;
		константен TEAM_MEMBER псевдоним currMember е dereferenceElement(members, it);

		cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << left << setw(colNoWidth) << loopCounter
			 << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << setw(colFirstNameWidth)
			 << dereferenceElement(parentSchool.students, currMember.username).firstName << setw(colLastNameWidth)
			 << dereferenceElement(parentSchool.students, currMember.username).lastName << setw(colEmailWidth)
			 << dereferenceElement(parentSchool.students, currMember.username).email << right << setw(colClassWidth - 4)
			 << dereferenceElement(parentSchool.students, currMember.username).grade << left << ' ' << setw(3)
			 << dereferenceElement(parentSchool.students, currMember.username).classLetter << setw(colRoleWidth)
			 << toString(currMember.role) << край_на_ред;
	}

	cout.copyfmt(initialState);
	cout << getAnsiEscape(ANSI_ESCAPE::RESET);
}

безтипов listTable(константен vector<size_t> псевдоним keys, константен unordered_map<size_t, TEAM> псевдоним teams,
				   константен SCHOOL псевдоним parentSchool)
{
	ios initialState(нулев_указател);

	size_t colNoWidth, colNameWidth, colProjectWidth, colDateWidth, colMembersWidth, colStatusWidth;
	size_t loopCounter;
	низ labelNo, labelName, labelProject, labelDate, labelMembers, labelStatus;

	ако(keys.empty())
	{
		cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "There are currently no teams." << край_на_ред;
		върни;
	}

	initialState.copyfmt(cout);

	labelNo е "No.";
	labelName е "Name";
	labelProject е "Project";
	labelDate е "Setup date";
	labelMembers е "Members";
	labelStatus е "Status";

	colNoWidth е max((size_t)ceil(log10(keys.size())), labelNo.size()) плюс 2;
	colNameWidth е labelName.size();
	colProjectWidth е labelProject.size();
	colDateWidth е max(10ull плюс 2, labelDate.size());
	colMembersWidth е labelMembers.size() плюс 2;
	colStatusWidth е labelStatus.size();

	за(auto it е keys.begin(); it не_е_равно_на keys.end(); it плюс_плюс)
	{
		константен TEAM псевдоним currTeam е dereferenceElement(teams, *it);

		colNameWidth е max(colNameWidth, currTeam.name.size());
		colProjectWidth е max(colProjectWidth, dereferenceElement(parentSchool.projects, currTeam.project).name.size());
		colStatusWidth е max(colStatusWidth, toString(currTeam.status).size());
	}

	colNameWidth плюс_равно 2;
	colProjectWidth плюс_равно 2;
	colStatusWidth плюс_равно 2;

	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << left << setw(colNoWidth) << labelNo << setw(colNameWidth)
		 << labelName << setw(colProjectWidth) << labelProject << setw(colDateWidth) << labelDate
		 << setw(colMembersWidth) << labelMembers << setw(colStatusWidth) << labelStatus << край_на_ред;

	cout << низ(colNoWidth притури colNameWidth притури colProjectWidth притури colDateWidth притури colMembersWidth
					притури colStatusWidth,
				'-')
		 << край_на_ред;

	loopCounter е 0;
	за(auto it е keys.begin(); it не_е_равно_на keys.end(); it плюс_плюс)
	{
		loopCounter плюс_плюс;
		константен TEAM псевдоним currTeam е dereferenceElement(teams, *it);

		cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << left << setw(colNoWidth) << loopCounter
			 << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << setw(colNameWidth) << currTeam.name << setw(colProjectWidth)
			 << dereferenceElement(parentSchool.projects, currTeam.project).name << setw(colDateWidth)
			 << currTeam.setupDate << setw(colMembersWidth) << currTeam.members.size() << setw(colStatusWidth)
			 << toString(currTeam.status) << край_на_ред;
	}

	cout.copyfmt(initialState);
	cout << getAnsiEscape(ANSI_ESCAPE::RESET);
}

безтипов listTable(константен vector<низ> псевдоним keys, константен unordered_map<низ, TEACHER> псевдоним teachers,
				   константен SCHOOL псевдоним parentSchool)
{
	ios initialState(нулев_указател);

	size_t colNoWidth, colFirstNameWidth, colLastNameWidth, colEmailWidth, colTeamsWidth;
	size_t loopCounter;
	низ labelNo, labelFirstName, labelLastName, labelEmail, labelTeams;

	ако(teachers.empty())
	{
		cout << getAnsiEscape(ANSI_ESCAPE::FG_RED) << "There are currently no teachers." << край_на_ред;
		върни;
	}

	initialState.copyfmt(cout);

	labelNo е "No.";
	labelFirstName е "First name";
	labelLastName е "Last name";
	labelEmail е "Email";
	labelTeams е "Assigned teams";

	colNoWidth е max((size_t)ceil(log10(teachers.size())), labelNo.size()) плюс 2;
	colFirstNameWidth е labelFirstName.size();
	colLastNameWidth е labelLastName.size();
	colEmailWidth е labelEmail.size();
	colTeamsWidth е labelTeams.size() плюс 2;

	за(auto it е keys.begin(); it не_е_равно_на keys.end(); it плюс_плюс)
	{
		константен TEACHER псевдоним currTeacher е dereferenceElement(teachers, *it);

		colFirstNameWidth е max(colFirstNameWidth, currTeacher.firstName.size());
		colLastNameWidth е max(colLastNameWidth, currTeacher.lastName.size());
		colEmailWidth е max(colEmailWidth, currTeacher.email.size());
	}

	colFirstNameWidth плюс_равно 2;
	colLastNameWidth плюс_равно 2;
	colEmailWidth плюс_равно 2;

	cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << left << setw(colNoWidth) << labelNo << setw(colFirstNameWidth)
		 << labelFirstName << setw(colLastNameWidth) << labelLastName << setw(colEmailWidth) << labelEmail
		 << setw(colTeamsWidth) << labelTeams << край_на_ред;

	cout << низ(colNoWidth притури colFirstNameWidth притури colLastNameWidth притури colEmailWidth притури
					colTeamsWidth,
				'-')
		 << край_на_ред;

	loopCounter е 0;
	за(auto it е keys.begin(); it не_е_равно_на keys.end(); it плюс_плюс)
	{
		loopCounter плюс_плюс;
		константен TEACHER псевдоним currTeacher е dereferenceElement(teachers, *it);

		cout << getAnsiEscape(ANSI_ESCAPE::FG_CYAN) << left << setw(colNoWidth) << loopCounter
			 << getAnsiEscape(ANSI_ESCAPE::FG_GREEN) << setw(colFirstNameWidth) << currTeacher.firstName
			 << setw(colLastNameWidth) << currTeacher.lastName << setw(colEmailWidth) << currTeacher.email
			 << setw(colTeamsWidth) << currTeacher.teams.size() << край_на_ред;
	}

	cout.copyfmt(initialState);
	cout << getAnsiEscape(ANSI_ESCAPE::RESET);
}
