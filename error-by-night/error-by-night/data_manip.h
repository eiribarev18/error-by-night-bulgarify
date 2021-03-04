#pragma once

#include "structures.h"

template <typename T>
bool addElement(std::vector<T> &v, const T &element)
{
	auto it = find(v.begin(), v.end(), element);

	if (it != v.end()) return false;

	v.push_back(element);

	return true;
}

bool addElement(std::vector<SCHOOL> &v, const SCHOOL &school);

template <typename KEY, typename T>
bool addElement(std::unordered_map<KEY, T> &m, const KEY &key, const T &element)
{
	return m.insert({key, element}).second;
}

template <typename T>
bool deleteElement(std::vector<T> &v, const T &element)
{
	auto it = find(v.begin(), v.end(), element);

	if (it == v.end()) return false;

	v.erase(it);

	return true;
}

bool deleteElement(std::vector<SCHOOL> &v, const std::string &name);

template <typename KEY, typename T>
bool deleteElement(std::unordered_map<KEY, T> &m, const KEY &key)
{
	return m.erase(key);
}
