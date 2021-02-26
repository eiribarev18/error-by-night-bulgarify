#include "data_manip.h"

#include "structures.h"

using namespace std;

bool addSchool(vector<SCHOOL> &schools, const SCHOOL &school)
{
	auto it = find_if(schools.begin(), schools.end(), [&school](const SCHOOL &currSchool) {
		return currSchool.name == school.name;
	});

	if (it != schools.end()) return false;

	schools.push_back(school);

	return true;
}

bool deleteSchool(vector<SCHOOL> &schools, const string &name)
{
	auto it = find_if(schools.begin(), schools.end(), [&name](const SCHOOL &currSchool) {
		return currSchool.name == name;
	});

	if (it == schools.end()) return false;

	schools.erase(it);

	return true;
}
