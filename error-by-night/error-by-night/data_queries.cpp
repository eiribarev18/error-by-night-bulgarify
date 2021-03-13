#include "data_manip.h"
#include "structures.h"

using namespace std;

vector<string> SCHOOL::getTeachersWithoutTeam(const string &project) const
{
	vector<string> out;

	for (auto it = teachers.begin(); it != teachers.end(); it++) {
		const TEACHER &currTeacher = dereferenceElement(teachers, it);

		auto foundIt = find_if(currTeacher.teams.begin(), currTeacher.teams.end(), [&project, this](size_t currTeam) {
			return project == dereferenceElement(this->teams, currTeam).project;
		});

		if (foundIt == currTeacher.teams.end()) out.push_back(it->first);
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
