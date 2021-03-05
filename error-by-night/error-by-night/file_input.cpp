#include "data_manip.h"
#include "file_io.h"
#include "structures.h"

#include <iostream>

using namespace std;

// T must be an unsigned integer type
template <typename T>
bool fileGetUnsignedNumber(ifstream &file, T &x, char delimiter = '\n', unsigned long long maxValue = -1)
{
	string raw;

	getline(file, raw, delimiter);

	for (size_t i = 0; i < raw.size(); i++) {
		if (raw[i] < '0' or raw[i] > '9') throw runtime_error("Non-digit character encountered");
	}

	x = (T)stoull(raw);

	if ((unsigned long long)x > maxValue) throw out_of_range("Number " + to_string((unsigned long long)x) + " is larger than maxValue=" + to_string(maxValue));

	return true;
}

bool restoreSchools(vector<SCHOOL> &schools, const string &filename)
{
	ifstream file(filename);
	size_t schoolsSize;
	SCHOOL currSchool;

	file.exceptions(ifstream::failbit | ifstream::badbit);

	if (!file.good()) return false;

	schools.clear();

	try {
		if (!fileGetUnsignedNumber(file, schoolsSize)) return false;

		schools.reserve(schoolsSize);

		for (size_t i = 0; i < schoolsSize; i++) {
			if (!currSchool.restore(file)) return false;
			addElement(schools, currSchool);
		}
	}
	catch (exception &e) {
		cerr << "Master restore encountered exception: " << e.what() << endl;

		return false;
	}

	return true;
}

bool SCHOOL::restore(ifstream &file)
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
	fileGetUnsignedNumber(file, mapSize);
	for (size_t i = 0; i < mapSize; i++) {
		getline(file, currKey);
		currStudent.restore(file);

		addElement(students, currKey, currStudent);
	}

	// teachers
	teachers.clear();
	fileGetUnsignedNumber(file, mapSize);
	for (size_t i = 0; i < mapSize; i++) {
		getline(file, currKey);
		currTeacher.restore(file);

		addElement(teachers, currKey, currTeacher);
	}

	// teams
	teams.clear();
	fileGetUnsignedNumber(file, mapSize);
	for (size_t i = 0; i < mapSize; i++) {
		fileGetUnsignedNumber(file, ucurrKey);
		currTeam.restore(file);

		addElement(teams, ucurrKey, currTeam);
	}

	// projects
	projects.clear();
	fileGetUnsignedNumber(file, mapSize);
	for (size_t i = 0; i < mapSize; i++) {
		getline(file, currKey);
		currProject.restore(file);

		addElement(projects, currKey, currProject);
	}

	return true;
}

bool STUDENT::restore(ifstream &file)
{
	string stemp;

	getline(file, firstName, ' ');
	getline(file, lastName);
	getline(file, email);
	fileGetUnsignedNumber(file, grade, ' ');

	getline(file, stemp);
	classLetter = stemp[0];

	return true;
}

bool TEACHER::restore(ifstream &file)
{
	size_t vectorSize, utemp;

	getline(file, firstName, ' ');
	getline(file, lastName);
	getline(file, email);

	fileGetUnsignedNumber(file, vectorSize);
	teams.clear();
	for (size_t i = 0; i < vectorSize; i++) {
		fileGetUnsignedNumber(file, utemp);

		addElement(teams, utemp);
	}

	return true;
}

bool TEAM::restore(ifstream &file)
{
	size_t vectorSize;
	TEAM_MEMBER currMember;

	getline(file, name);
	getline(file, description);
	getline(file, setupDate);

	fileGetUnsignedNumber(file, vectorSize);
	members.clear();
	for (size_t i = 0; i < vectorSize; i++) {
		getline(file, currMember.username, ' ');
		fileGetUnsignedNumber(file, currMember.role, '\n', 3);

		addElement(members, currMember);
	}

	fileGetUnsignedNumber(file, status, '\n', 1);
	getline(file, project);

	return true;
}

bool PROJECT::restore(ifstream &file)
{
	size_t vectorSize, utemp;

	getline(file, name);
	getline(file, description, '|');
	file.ignore();
	fileGetUnsignedNumber(file, status, '\n', 1);

	fileGetUnsignedNumber(file, vectorSize);
	teams.clear();
	for (size_t i = 0; i < vectorSize; i++) {
		fileGetUnsignedNumber(file, utemp);

		addElement(teams, utemp);
	}

	return true;
}
