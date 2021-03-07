#pragma once

#include "structures.h"

#include <fstream>
#include <string>
#include <vector>

bool restoreSchools(std::vector<SCHOOL> &schools, const std::string &filename);
bool storeSchools(const std::vector<SCHOOL> &schools, const std::string &filename);

// T must be an unsigned integer type
template <typename T>
void getUnsignedNumber(std::istream &stream, T &x, char delimiter = '\n', unsigned long long maxValue = -1, unsigned long long minValue = 0)
{
	std::string raw;

	std::getline(stream, raw, delimiter);

	for (size_t i = 0; i < raw.size(); i++) {
		if (raw[i] < '0' or raw[i] > '9') throw std::runtime_error("Non-digit character encountered");
	}

	if (stoull(raw) > maxValue) throw std::out_of_range("Number " + std::to_string((unsigned long long)x) + " is larger than maxValue=" + std::to_string(maxValue));
	if (stoull(raw) < minValue) throw std::out_of_range("Number " + std::to_string((unsigned long long)x) + " is smaller than minValue=" + std::to_string(maxValue));

	x = (T)stoull(raw);
}
