#include "file_io.h"
#include "structures.h"
#include "data_manip.h"

#include <iostream>

using namespace std;

bool storeSchools(const vector<SCHOOL> &schools, const string &filename)
{
	ofstream file(filename, ios::out | ios::trunc);

	file.exceptions(ios::failbit | ios::badbit);

	try {
		file << schools.size() << '\n';

		for (auto it = schools.begin(); it != schools.end(); it++) {
			dereferenceElement(schools, it).store(file);
		}
	}
	catch (exception &e) {
		cerr << "Master store encountered exception: " << e.what() << endl;

		return false;
	}

	return true;
}

void SCHOOL::store(ofstream &file) const
{
	file << name << '\n'
		 << city << '\n'
		 << address << '\n';

	// students
	file << students.size() << '\n';
	for (auto it = students.begin(); it != students.end(); it++) {
		file << it->first << '\n';
		it->second.store(file);
	}

	// teachers
	file << teachers.size() << '\n';
	for (auto it = teachers.begin(); it != teachers.end(); it++) {
		file << it->first << '\n';
		it->second.store(file);
	}

	// teams
	file << teams.size() << '\n';
	for (auto it = teams.begin(); it != teams.end(); it++) {
		file << it->first << '\n';
		it->second.store(file);
	}

	// projects
	file << projects.size() << '\n';
	for (auto it = projects.begin(); it != projects.end(); it++) {
		file << it->first << '\n';
		it->second.store(file);
	}
}

void STUDENT::store(ofstream &file) const
{
	file << firstName << ' ' << lastName << '\n'
		 << email << '\n'
		 << grade << ' ' << classLetter << '\n';
}

void TEACHER::store(ofstream &file) const
{
	file << firstName << ' ' << lastName << '\n'
		 << email << '\n';

	file << teams.size() << '\n';
	for (auto it = teams.begin(); it != teams.end(); it++) {
		file << *it << '\n';
	}
}

void TEAM::store(ofstream &file) const
{
	file << name << '\n'
		 << description << '\n'
		 << setupDate << '\n';

	file << members.size() << '\n';
	for (auto it = members.begin(); it != members.end(); it++) {
		file << it->username << ' ' << it->role << '\n';
	}

	file << (unsigned)status << '\n'
		 << project << '\n';
}

void PROJECT::store(ofstream &file) const
{
	file << name << '\n'
		 << description << "|\n"
		 << (unsigned)status << '\n';

	file << teams.size() << '\n';
	for (auto it = teams.begin(); it != teams.end(); it++) {
		file << *it << '\n';
	}
}
