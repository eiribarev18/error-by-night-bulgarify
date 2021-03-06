#include "structures.h"

using namespace std;

bool operator==(const TEAM_MEMBER &lhs, const TEAM_MEMBER &rhs)
{
	return lhs.username == rhs.username and lhs.role == rhs.role;
}

string toString(STATUS status)
{
	vector<const char *> translation = { "ACTIVE",
										 "ARCHIVED" };

	return translation[(size_t)status];
}
