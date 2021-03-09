#include "data_manip.h"

#include "structures.h"

using namespace std;

bool addElement(vector<SCHOOL> &v, const SCHOOL &school)
{
	auto it = find_if(v.begin(), v.end(), [&school](const SCHOOL &currSchool) {
		return currSchool.name == school.name;
	});

	if (it != v.end()) return false;

	v.push_back(school);

	return true;
}
