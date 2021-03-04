#include "structures.h"

using namespace std;

vector<string> SCHOOL::getTeachersWithoutTeam() const
{
	vector<string> out;

	for (auto it = teachers.begin(); it != teachers.end(); it++) {
		if (it->second.teams.empty()) out.push_back(it->first);
	}

	return out;
}

vector<string> TEAM::getMembers() const
{
	vector<string> out;

	for (auto it = members.begin(); it != members.end(); it++) {
		out.push_back(it->username);
	}

	return out;
}
