#pragma once

#include "structures.h"

#include <fstream>
#include <string>
#include <vector>

bool restoreSchools(std::vector<SCHOOL> &schools, const std::string &filename);
bool storeSchools(const std::vector<SCHOOL> &schools, const std::string &filename);
