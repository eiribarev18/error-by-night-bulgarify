#include "console_io.h"
#include "data_manip.h"
#include "structures.h"

using namespace std;

bool operator==(const TEAM_MEMBER &lhs, const TEAM_MEMBER &rhs)
{
	return lhs.username == rhs.username and lhs.role == rhs.role;
}

string toString(STATUS status)
{
	vector<const char *> translation = {"ACTIVE", "ARCHIVED"};

	return translation[(size_t)status];
}

string toString(TEAM_MEMBER::ROLE role)
{
	vector<const char *> translation = {"SCRUM MASTER", "QA ENGINEER", "BACKEND DEV", "FRONTEND DEV"};

	return translation[(size_t)role];
}

string getAnsiEscape(ANSI_ESCAPE colour)
{
	string out = "\033[";

	out += to_string((int)colour);
	out += "m";

	return out;
}

bool isValidKey(const string &key)
{
	return key != "INVALID";
}

bool isValidKey(size_t key)
{
	return key != 0;
}
