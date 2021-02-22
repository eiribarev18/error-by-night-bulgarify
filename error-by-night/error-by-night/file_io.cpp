#include "file_io.h"

#include "structures.h"

using namespace std;

bool fileGetNumber(ifstream &file, size_t &x, char delimiter = '\n')
{
	size_t out = 0;
	string raw;

	if (!getline(file, raw, delimiter)) return false;

	for (size_t i = 0; i < raw.size(); i++) {
		if (raw[i] < '0' or raw[i] > '9') return false;
		out += raw[i] - '0';
	}

	x = out;

	return true;
}

bool fileGetNumber(ifstream &file, unsigned &x, char delimiter = '\n')
{
	unsigned out = 0;
	string raw;

	if (!getline(file, raw, delimiter)) return false;

	for (size_t i = 0; i < raw.size(); i++) {
		if (raw[i] < '0' or raw[i] > '9') return false;
		out *= 10;
		out += raw[i] - '0';
	}

	x = out;

	return true;
}

bool restoreSchools(vector<SCHOOL> &schools, string filename)
{
	ifstream file(filename);
	size_t schoolsSize;
	SCHOOL currSchool;

	if (!file.good()) return false;

	schools.clear();

	if (!fileGetNumber(file, schoolsSize)) return false;

	schools.reserve(schoolsSize);

	for (size_t i = 0; i < schoolsSize; i++) {
		if (!currSchool.restore(file)) return false;
		schools.push_back(currSchool);
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

	if (!getline(file, temp)) return false;
	name = temp;

	if (!getline(file, temp)) return false;
	city = temp;

	if (!getline(file, temp)) return false;
	address = temp;

	// students
	if (!fileGetNumber(file, mapSize)) return false;
	for (size_t i = 0; i < mapSize; i++) {
		if (!getline(file, currKey)) return false;
		if (!currStudent.restore(file)) return false;

		students.insert({currKey, currStudent});
	}

	// teachers
	if (!fileGetNumber(file, mapSize)) return false;
	for (size_t i = 0; i < mapSize; i++) {
		if (!getline(file, currKey)) return false;
		if (!currTeacher.restore(file)) return false;

		teachers.insert({currKey, currTeacher});
	}

	// teams
	if (!fileGetNumber(file, mapSize)) return false;
	for (size_t i = 0; i < mapSize; i++) {
		if (!fileGetNumber(file, ucurrKey)) return false;
		if (!currTeam.restore(file)) return false;

		teams.insert({ucurrKey, currTeam});
	}

	return true;
}

bool STUDENT::restore(ifstream &file)
{
	string stemp;
	unsigned utemp;

	if (!getline(file, stemp, ' ')) return false;
	firstName = stemp;

	if (!getline(file, stemp)) return false;
	lastName = stemp;

	if (!getline(file, stemp)) return false;
	email = stemp;

	if (!fileGetNumber(file, utemp, ' ')) return false;
	grade = utemp;

	if (!getline(file, stemp)) return false;
	classLetter = stemp[0];

	return true;
}

bool TEACHER::restore(ifstream &file)
{
	string stemp;
	size_t vectorSize, utemp;

	if (!getline(file, stemp, ' ')) return false;
	firstName = stemp;

	if (!getline(file, stemp)) return false;
	lastName = stemp;

	if (!getline(file, stemp)) return false;
	email = stemp;

	if (!fileGetNumber(file, vectorSize)) return false;
	teamIDs.clear();
	for (size_t i = 0; i < vectorSize; i++) {
		if (!fileGetNumber(file, utemp)) return false;
		teamIDs.push_back(utemp);
	}

	return true;
}

bool TEAM::restore(ifstream &file)
{
	string stemp;
	size_t vectorSize;

	if (!getline(file, stemp)) return false;
	name = stemp;

	if (!getline(file, stemp)) return false;
	description = stemp;

	if (!getline(file, stemp)) return false;
	setupDate = stemp;

	if (!fileGetNumber(file, vectorSize)) return false;
	memberUsernames.clear();
	for (size_t i = 0; i < vectorSize; i++) {
		if (!getline(file, stemp)) return false;
		memberUsernames.push_back(stemp);
	}

	return true;
}
