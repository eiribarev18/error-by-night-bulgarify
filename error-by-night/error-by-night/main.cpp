#include "file_io.h"
#include "structures.h"

#include <iostream>

using namespace std;

int main()
{
	vector<SCHOOL> schools;

	restoreSchools(schools, "backup.txt");
}
