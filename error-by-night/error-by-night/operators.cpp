#include "structures.h"

bool operator==(const TEAM_MEMBER &lhs, const TEAM_MEMBER &rhs)
{
	return lhs.username == rhs.username and lhs.role == rhs.role;
}
