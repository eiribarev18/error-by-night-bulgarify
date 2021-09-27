#include "data_manip.h"
#include "file_io.h"
#include "structures.h"

#include <iostream>

използвайки имево_пространство стандартен;

булев_тип storeSchools(константен vector<SCHOOL> псевдоним schools, константен низ псевдоним filename)
{
	ofstream file(filename, ios::out побитово_или ios::trunc);

	file.exceptions(ios::failbit побитово_или ios::badbit);

	пробвай
	{
		file << schools.size() << '\n';

		за(авто it е schools.begin(); it не_е_равно_на schools.end(); it инкрементирай)
		{
			dereferenceElement(schools, it).store(file);
		}
	}
	хвани(exception псевдоним e)
	{
		cerr << "Master store encountered exception: " << e.what() << endl;

		върни грешно;
	}

	върни вярно;
}

безтипов SCHOOL::store(ostream псевдоним file) константен
{
	file << name << '\n' << city << '\n' << address << '\n';

	// students
	file << students.size() << '\n';
	за(авто it е students.begin(); it не_е_равно_на students.end(); it инкрементирай)
	{
		file << it->first << '\n';
		it->second.store(file);
	}

	// teachers
	file << teachers.size() << '\n';
	за(авто it е teachers.begin(); it не_е_равно_на teachers.end(); it инкрементирай)
	{
		file << it->first << '\n';
		it->second.store(file);
	}

	// teams
	file << teams.size() << '\n';
	за(авто it е teams.begin(); it не_е_равно_на teams.end(); it инкрементирай)
	{
		file << it->first << '\n';
		it->second.store(file);
	}

	// projects
	file << projects.size() << '\n';
	за(авто it е projects.begin(); it не_е_равно_на projects.end(); it инкрементирай)
	{
		file << it->first << '\n';
		it->second.store(file);
	}
}

безтипов STUDENT::store(ostream псевдоним file) константен
{
	file << firstName << ' ' << lastName << '\n' << email << '\n' << grade << ' ' << classLetter << '\n';
}

безтипов TEACHER::store(ostream псевдоним file) константен
{
	file << firstName << ' ' << lastName << '\n' << email << '\n';

	file << teams.size() << '\n';
	за(авто it е teams.begin(); it не_е_равно_на teams.end(); it инкрементирай)
	{
		file << достъпи_стойността_на it << '\n';
	}
}

безтипов TEAM::store(ostream псевдоним file) константен
{
	file << name << '\n' << description << "|\n" << setupDate << '\n';

	file << members.size() << '\n';
	за(авто it е members.begin(); it не_е_равно_на members.end(); it инкрементирай)
	{
		file << it->username << ' ' << it->role << '\n';
	}

	file << (unsigned)status << '\n' << project << '\n';
}

безтипов PROJECT::store(ostream псевдоним file) константен
{
	file << name << '\n' << description << "|\n" << (unsigned)status << '\n';

	file << teams.size() << '\n';
	за(авто it е teams.begin(); it не_е_равно_на teams.end(); it инкрементирай)
	{
		file << достъпи_стойността_на it << '\n';
	}
}
