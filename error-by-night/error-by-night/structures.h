#pragma once

#include "bulgarify/Bulgarify.h"

#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

изброим клас STATUS{ACTIVE, ARCHIVED};

структура STUDENT
{
	стандартен::низ firstName;
	стандартен::низ lastName;
	стандартен::низ email;
	беззнаков grade;
	символ classLetter;

	булев_тип restore(стандартен::istream псевдоним file);
	безтипов store(стандартен::ostream псевдоним file) константен;
};

структура TEACHER
{
	стандартен::низ firstName;
	стандартен::низ lastName;
	стандартен::низ email;
	стандартен::vector<size_t> teams;

	булев_тип restore(стандартен::istream псевдоним file);
	безтипов store(стандартен::ostream псевдоним file) константен;
};

структура TEAM_MEMBER
{
	изброим ROLE{SCRUM_MASTER, QA_ENGINEER, DEV_BACKEND, DEV_FRONTEND};

	стандартен::низ username;
	ROLE role;
};

структура TEAM
{
	стандартен::низ name;
	стандартен::низ description;
	стандартен::низ setupDate;
	стандартен::vector<TEAM_MEMBER> members;
	STATUS status;
	стандартен::string project;

	булев_тип restore(стандартен::istream псевдоним file);
	безтипов store(стандартен::ostream псевдоним file) константен;

	стандартен::vector<стандартен::низ> getMembers() константен;
};

структура PROJECT
{
	стандартен::низ name;
	стандартен::низ description;
	стандартен::vector<size_t> teams;
	STATUS status;

	булев_тип restore(стандартен::istream псевдоним file);
	безтипов store(стандартен::ostream псевдоним file) константен;
};

структура SCHOOL
{
	стандартен::низ name;
	стандартен::низ city;
	стандартен::низ address;
	стандартен::unordered_map<стандартен::низ, STUDENT> students;
	стандартен::unordered_map<стандартен::низ, TEACHER> teachers;
	стандартен::unordered_map<size_t, TEAM> teams;
	стандартен::unordered_map<стандартен::низ, PROJECT> projects;

	булев_тип restore(стандартен::istream псевдоним file);
	безтипов store(стандартен::ostream псевдоним file) константен;

	стандартен::vector<стандартен::низ> getTeachersWithoutTeam(константен стандартен::низ псевдоним project) константен;
};

булев_тип operator==(константен TEAM_MEMBER псевдоним lhs, константен TEAM_MEMBER псевдоним rhs);
стандартен::низ toString(STATUS status);
стандартен::низ toString(TEAM_MEMBER::ROLE role);
