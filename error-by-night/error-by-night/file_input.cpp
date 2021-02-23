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

	if (x > maxValue) throw out_of_range("Number " + to_string(x) + " is larger than maxValue=" + to_string(maxValue));

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
	students.clear();
	fileGetUnsignedNumber(file, mapSize);
	for (size_t i = 0; i < mapSize; i++) {
		getline(file, currKey);
		currStudent.restore(file);

		students.insert({currKey, currStudent});
	}

	// teachers
	teachers.clear();
	fileGetUnsignedNumber(file, mapSize);
	for (size_t i = 0; i < mapSize; i++) {
		getline(file, currKey);
		currTeacher.restore(file);

		teachers.insert({currKey, currTeacher});
	}

	// teams
	teams.clear();
	fileGetUnsignedNumber(file, mapSize);
	for (size_t i = 0; i < mapSize; i++) {
		fileGetUnsignedNumber(file, ucurrKey);
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

	fileGetUnsignedNumber(file, utemp, ' ');
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

	fileGetUnsignedNumber(file, vectorSize);
	teamIDs.clear();
	for (size_t i = 0; i < vectorSize; i++) {
		fileGetUnsignedNumber(file, utemp);
		teamIDs.push_back(utemp);
	}

	return true;
}

bool TEAM::restore(ifstream &file)
{
	string stemp;
	size_t vectorSize;
	TEAM_MEMBER currMember;

	getline(file, stemp);
	name = stemp;

	getline(file, stemp);
	description = stemp;

	getline(file, stemp);
	setupDate = stemp;

	fileGetUnsignedNumber(file, vectorSize);
	members.clear();
	for (size_t i = 0; i < vectorSize; i++) {
		getline(file, currMember.username, ' ');
		fileGetUnsignedNumber(file, currMember.role, '\n', 3);

		members.push_back(currMember);
	}

	fileGetUnsignedNumber(file, status, '\n', 1);

	return true;
}
