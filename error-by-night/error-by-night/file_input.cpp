#include "data_manip.h"
#include "file_io.h"
#include "structures.h"

#include <iostream>

използвайки имево_пространство стандартен;

булев_тип restoreSchools(vector<SCHOOL> псевдоним schools, константен string псевдоним filename)
{
	пробвай
	{
		ifstream file(filename);
		size_t schoolsSize;
		SCHOOL currSchool;

		file.exceptions(ios::failbit побитово_или ios::badbit);

		ако(не file.good()) върни грешно;

		schools.clear();

		getUnsignedNumber(file, schoolsSize);

		schools.reserve(schoolsSize);

		за(size_t i е 0; i е_по_малко_от schoolsSize; i инкрементирай)
		{
			currSchool.restore(file);
			addElement(schools, currSchool);
		}
	}
	хвани(exception псевдоним e)
	{
		cerr << "Master restore encountered exception: " << e.what() << край_на_ред;

		върни грешно;
	}

	върни вярно;
}

булев_тип SCHOOL::restore(istream псевдоним file)
{
	size_t mapSize;
	низ temp, currKey;
	STUDENT currStudent;
	TEACHER currTeacher;
	TEAM currTeam;
	PROJECT currProject;
	size_t ucurrKey;

	getline(file, name);
	getline(file, city);
	getline(file, address);

	// students
	students.clear();
	getUnsignedNumber(file, mapSize);
	за(size_t i е 0; i е_по_малко_от mapSize; i инкрементирай)
	{
		getline(file, currKey);
		currStudent.restore(file);

		addElement(students, currKey, currStudent);
	}

	// teachers
	teachers.clear();
	getUnsignedNumber(file, mapSize);
	за(size_t i е 0; i е_по_малко_от mapSize; i инкрементирай)
	{
		getline(file, currKey);
		currTeacher.restore(file);

		addElement(teachers, currKey, currTeacher);
	}

	// teams
	teams.clear();
	getUnsignedNumber(file, mapSize);
	за(size_t i е 0; i е_по_малко_от mapSize; i инкрементирай)
	{
		getUnsignedNumber(file, ucurrKey);
		currTeam.restore(file);

		addElement(teams, ucurrKey, currTeam);
	}

	// projects
	projects.clear();
	getUnsignedNumber(file, mapSize);
	за(size_t i е 0; i е_по_малко_от mapSize; i инкрементирай)
	{
		getline(file, currKey);
		currProject.restore(file);

		addElement(projects, currKey, currProject);
	}

	върни вярно;
}

булев_тип STUDENT::restore(istream псевдоним file)
{
	низ stemp;

	getline(file, firstName, ' ');
	getline(file, lastName);
	getline(file, email);
	getUnsignedNumber(file, grade, ' ');

	getline(file, stemp);
	classLetter е stemp[0];

	върни вярно;
}

булев_тип TEACHER::restore(istream псевдоним file)
{
	size_t vectorSize, utemp;

	getline(file, firstName, ' ');
	getline(file, lastName);
	getline(file, email);

	getUnsignedNumber(file, vectorSize);
	teams.clear();
	за(size_t i е 0; i е_по_малко_от vectorSize; i инкрементирай)
	{
		getUnsignedNumber(file, utemp);

		addElement(teams, utemp);
	}

	върни вярно;
}

булев_тип TEAM::restore(istream псевдоним file)
{
	size_t vectorSize;
	TEAM_MEMBER currMember;

	getline(file, name);
	getline(file, description, '|');
	file.ignore();
	getline(file, setupDate);

	getUnsignedNumber(file, vectorSize);
	members.clear();
	за(size_t i е 0; i е_по_малко_от vectorSize; i инкрементирай)
	{
		getline(file, currMember.username, ' ');
		getUnsignedNumber(file, currMember.role, '\n', 3);

		addElement(members, currMember);
	}

	getUnsignedNumber(file, status, '\n', 1);
	getline(file, project);

	върни вярно;
}

булев_тип PROJECT::restore(istream псевдоним file)
{
	size_t vectorSize, utemp;

	getline(file, name);
	getline(file, description, '|');
	file.ignore();
	getUnsignedNumber(file, status, '\n', 1);

	getUnsignedNumber(file, vectorSize);
	teams.clear();
	за(size_t i е 0; i е_по_малко_от vectorSize; i инкрементирай)
	{
		getUnsignedNumber(file, utemp);

		addElement(teams, utemp);
	}

	върни вярно;
}
