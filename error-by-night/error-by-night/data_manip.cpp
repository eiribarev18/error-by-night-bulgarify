#include "data_manip.h"

#include "structures.h"

използвайки имево_пространство стандартен;

булев_тип addElement(vector<SCHOOL> псевдоним v, константен SCHOOL псевдоним school)
{
	авто it е find_if(v.begin(), v.end(), [псевдоним school](константен SCHOOL псевдоним currSchool) {
		върни currSchool.name е_равно_на school.name;
	});

	ако(it не_е_равно_на v.end()) върни грешно;

	v.push_back(school);

	върни вярно;
}
