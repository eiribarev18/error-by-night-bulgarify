#include "file_io.h"

#include "structures.h"

#include <iostream>

using namespace std;

bool fileGetNumber(ifstream &file, size_t &x, char delimiter = '\n')
{
	string raw;

	getline(file, raw, delimiter);

	for (size_t i = 0; i < raw.size(); i++) {
		if (raw[i] < '0' or raw[i] > '9') throw runtime_error("Non-digit character encountered");
	}

	x = stoull(raw);

	return true;
}

bool fileGetNumber(ifstream &file, unsigned &x, char delimiter = '\n')
{
	string raw;

	getline(file, raw, delimiter);

	for (size_t i = 0; i < raw.size(); i++) {
		if (raw[i] < '0' or raw[i] > '9') throw runtime_error("Non-digit character encountered");
	}

	x = stoul(raw);

	return true;
}

bool restoreSchools(vector<SCHOOL> &schools, string filename)
{
	ifstream file(filename);
	size_t schoolsSize;
	SCHOOL currSchool;

	file.exceptions(ifstream::failbit | ifstream::badbit);

	if (!file.good()) return false;

	schools.clear();

	try {
		if (!fileGetNumber(file, schoolsSize)) return false;

		schools.reserve(schoolsSize);

		for (size_t i = 0; i < schoolsSize; i++) {
			if (!currSchool.restore(file)) return false;
			schools.push_back(currSchool);
		}
	}
	catch (exception &e) {
		cout << "Unable to restore from file due to exception" << endl;
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
	size_t ucurrKey;

	getline(file, temp);
	name = temp;

	getline(file, temp);
	city = temp;

	getline(file, temp);
	address = temp;

	// students
	fileGetNumber(file, mapSize);
	for (size_t i = 0; i < mapSize; i++) {
		getline(file, currKey);
		currStudent.restore(file);

		students.insert({currKey, currStudent});
	}

	// teachers
	fileGetNumber(file, mapSize);
	for (size_t i = 0; i < mapSize; i++) {
		getline(file, currKey);
		currTeacher.restore(file);

		teachers.insert({currKey, currTeacher});
	}

	// teams
	fileGetNumber(file, mapSize);
	for (size_t i = 0; i < mapSize; i++) {
		fileGetNumber(file, ucurrKey);
		currTeam.restore(file);

		teams.insert({ucurrKey, currTeam});
	}

	return true;
}

bool STUDENT::restore(ifstream &file)
{
	string stemp;
	unsigned utemp;

	getline(file, stemp, ' ');
	firstName = stemp;

	getline(file, stemp);
	lastName = stemp;

	getline(file, stemp);
	email = stemp;

	fileGetNumber(file, utemp, ' ');
	grade = utemp;

	getline(file, stemp);
	classLetter = stemp[0];

	return true;
}

bool TEACHER::restore(ifstream &file)
{
	string stemp;
	size_t vectorSize, utemp;

	getline(file, stemp, ' ');
	firstName = stemp;

	getline(file, stemp);
	lastName = stemp;

	getline(file, stemp);
	email = stemp;

	fileGetNumber(file, vectorSize);
	teamIDs.clear();
	for (size_t i = 0; i < vectorSize; i++) {
		fileGetNumber(file, utemp);
		teamIDs.push_back(utemp);
	}

	return true;
}

bool TEAM::restore(ifstream &file)
{
	string stemp;
	size_t vectorSize;

	getline(file, stemp);
	name = stemp;

	getline(file, stemp);
	description = stemp;

	getline(file, stemp);
	setupDate = stemp;

	fileGetNumber(file, vectorSize);
	memberUsernames.clear();
	for (size_t i = 0; i < vectorSize; i++) {
		getline(file, stemp);
		memberUsernames.push_back(stemp);
	}

	return true;
}
