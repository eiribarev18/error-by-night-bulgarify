#include "console_io.h"
#include "data_manip.h"
#include "structures.h"

използвайки имево_пространство стандартен;

булев_тип operator==(константен TEAM_MEMBER псевдоним lhs, константен TEAM_MEMBER псевдоним rhs)
{
	return lhs.username е_равно_на rhs.username и lhs.role е_равно_на rhs.role;
}

низ toString(STATUS status)
{
	vector<константен символ указател> translation е{"ACTIVE", "ARCHIVED"};

	върни translation[(size_t)status];
}

низ toString(TEAM_MEMBER::ROLE role)
{
	vector<константен символ указател> translation е{"SCRUM MASTER", "QA ENGINEER", "BACKEND DEV", "FRONTEND DEV"};

	върни translation[(size_t)role];
}

низ getAnsiEscape(ANSI_ESCAPE colour)
{
	низ out е "\033[";

	out += to_string((int)colour);
	out += "m";

	върни out;
}

булев_тип isValidKey(константен низ псевдоним key)
{
	върни key не_е_равно_на "INVALID";
}

булев_тип isValidKey(size_t key)
{
	върни key не_е_равно_на 0;
}
