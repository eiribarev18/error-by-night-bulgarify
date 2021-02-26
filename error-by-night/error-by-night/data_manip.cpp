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

bool SCHOOL::addStudent(const STUDENT &student, const string &username)
{
	return students.insert({username, student}).second;
}

bool SCHOOL::deleteStudent(const string &username)
{
	return students.erase(username);
}

bool SCHOOL::addTeacher(const TEACHER &teacher, const string &username)
{
	return teachers.insert({username, teacher}).second;
}

bool SCHOOL::deleteTeacher(const string &username)
{
	return teachers.erase(username);
}

bool SCHOOL::addTeam(const TEAM &team, size_t id)
{
	return teams.insert({id, team}).second;
}

bool SCHOOL::deleteTeam(size_t id)
{
	return teams.erase(id);
}
