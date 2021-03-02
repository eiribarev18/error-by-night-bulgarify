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

bool SCHOOL::addProject(const PROJECT &project, const string &id)
{
	return projects.insert({id, project}).second;
}

bool SCHOOL::deleteProject(const string &id)
{
	return projects.erase(id);
}

bool PROJECT::addTeam(size_t id)
{
	auto it = find(teams.begin(), teams.end(), id);

	if (it != teams.end()) return false;

	teams.push_back(id);

	return true;
}

bool PROJECT::deleteTeam(size_t id)
{
	auto it = find(teams.begin(), teams.end(), id);

	if (it == teams.end()) return false;

	teams.erase(it);

	return true;
}

bool TEAM::addMember(const TEAM_MEMBER &member)
{
	auto it = find_if(members.begin(), members.end(), [&member](const TEAM_MEMBER &currMember) {
		// should maybe just overload operator== instead
		return currMember.username == member.username and currMember.role == member.role;
	});

	if (it != members.end()) return false;

	members.push_back(member);

	return true;
}

bool TEAM::deleteMember(const string &username)
{
	auto it = find_if(members.begin(), members.end(), [&username](const TEAM_MEMBER &currMember) {
		return currMember.username == username;
	});

	if (it == members.end()) return false;

	members.erase(it);

	return true;
}

bool TEACHER::addTeam(size_t id)
{
	auto it = find(teamIDs.begin(), teamIDs.end(), id);

	if (it != teamIDs.end()) return false;

	teamIDs.push_back(id);

	return true;
}

bool TEACHER::deleteTeam(size_t id)
{
	auto it = find(teamIDs.begin(), teamIDs.end(), id);

	if (it == teamIDs.end()) return false;

	teamIDs.erase(it);

	return true;
}
