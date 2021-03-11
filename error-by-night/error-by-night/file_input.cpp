#include "data_manip.h"
#include "file_io.h"
#include "structures.h"

#include <iostream>

using namespace std;

bool restoreSchools(vector<SCHOOL> &schools, const string &filename)
{
	ifstream file(filename);
	size_t schoolsSize;
	SCHOOL currSchool;

	file.exceptions(ios::failbit | ios::badbit);

	if (!file.good()) return false;

	schools.clear();

	try {
		getUnsignedNumber(file, schoolsSize);

		schools.reserve(schoolsSize);

		for (size_t i = 0; i < schoolsSize; i++) {
			currSchool.restore(file);
			addElement(schools, currSchool);
		}
	}
	catch (exception &e) {
		cerr << "Master restore encountered exception: " << e.what() << endl;

		return false;
	}

	return true;
}

bool SCHOOL::restore(istream &file)
{
	size_t mapSize;
	string temp, currKey;
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
	for (size_t i = 0; i < mapSize; i++) {
		getline(file, currKey);
		currStudent.restore(file);

		addElement(students, currKey, currStudent);
	}

	// teachers
	teachers.clear();
	getUnsignedNumber(file, mapSize);
	for (size_t i = 0; i < mapSize; i++) {
		getline(file, currKey);
		currTeacher.restore(file);

		addElement(teachers, currKey, currTeacher);
	}

	// teams
	teams.clear();
	getUnsignedNumber(file, mapSize);
	for (size_t i = 0; i < mapSize; i++) {
		getUnsignedNumber(file, ucurrKey);
		currTeam.restore(file);

		addElement(teams, ucurrKey, currTeam);
	}

	// projects
	projects.clear();
	getUnsignedNumber(file, mapSize);
	for (size_t i = 0; i < mapSize; i++) {
		getline(file, currKey);
		currProject.restore(file);

		addElement(projects, currKey, currProject);
	}

	return true;
}

bool STUDENT::restore(istream &file)
{
	string stemp;

	getline(file, firstName, ' ');
	getline(file, lastName);
	getline(file, email);
	getUnsignedNumber(file, grade, ' ');

	getline(file, stemp);
	classLetter = stemp[0];

	return true;
}

bool TEACHER::restore(istream &file)
{
	size_t vectorSize, utemp;

	getline(file, firstName, ' ');
	getline(file, lastName);
	getline(file, email);

	getUnsignedNumber(file, vectorSize);
	teams.clear();
	for (size_t i = 0; i < vectorSize; i++) {
		getUnsignedNumber(file, utemp);

		addElement(teams, utemp);
	}

	return true;
}

bool TEAM::restore(istream &file)
{
	size_t vectorSize;
	TEAM_MEMBER currMember;

	getline(file, name);
	getline(file, description, '|');
	file.ignore();
	getline(file, setupDate);

	getUnsignedNumber(file, vectorSize);
	members.clear();
	for (size_t i = 0; i < vectorSize; i++) {
		getline(file, currMember.username, ' ');
		getUnsignedNumber(file, currMember.role, '\n', 3);

		addElement(members, currMember);
	}

	getUnsignedNumber(file, status, '\n', 1);
	getline(file, project);

	return true;
}

bool PROJECT::restore(istream &file)
{
	size_t vectorSize, utemp;

	getline(file, name);
	getline(file, description, '|');
	file.ignore();
	getUnsignedNumber(file, status, '\n', 1);

	getUnsignedNumber(file, vectorSize);
	teams.clear();
	for (size_t i = 0; i < vectorSize; i++) {
		getUnsignedNumber(file, utemp);

		addElement(teams, utemp);
	}

	return true;
}
