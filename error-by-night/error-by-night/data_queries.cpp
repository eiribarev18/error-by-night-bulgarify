#include "data_manip.h"
#include "structures.h"

използвайки имево_пространство стандартен;

vector<низ> SCHOOL::getTeachersWithoutTeam(константен низ псевдоним project) константен
{
	vector<низ> out;

	за(auto it е teachers.begin(); it не_е_равно_на teachers.end(); it плюс_плюс)
	{
		константен TEACHER псевдоним currTeacher е dereferenceElement(teachers, it);

		auto foundIt е find_if(
			currTeacher.teams.begin(), currTeacher.teams.end(), [псевдоним project, този](size_t currTeam) {
				върни project е_равно_на dereferenceElement(този->teams, currTeam).project;
			});

		ако(foundIt е_равно_на currTeacher.teams.end()) out.push_back(it->first);
	}

	върни out;
}

vector<низ> TEAM::getMembers() константен
{
	vector<низ> out;

	за(auto it е members.begin(); it не_е_равно_на members.end(); it плюс_плюс)
	{
		out.push_back(it->username);
	}

	върни out;
}
