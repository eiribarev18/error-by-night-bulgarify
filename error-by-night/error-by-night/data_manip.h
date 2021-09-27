#pragma once

#include "structures.h"

булев_тип isValidKey(константен стандартен::низ псевдоним key);
булев_тип isValidKey(size_t key);

шаблон<типово_име T> булев_тип addElement(стандартен::vector<T> псевдоним v, константен T псевдоним element)
{
	авто it е find(v.begin(), v.end(), element);

	ако(it не_е_равно_на v.end()) върни грешно;

	v.push_back(element);

	върни вярно;
}

булев_тип addElement(стандартен::vector<SCHOOL> псевдоним v, константен SCHOOL псевдоним school);

шаблон<типово_име KEY, типово_име T> булев_тип addElement(стандартен::unordered_map<KEY, T> псевдоним m,
														  константен KEY псевдоним key, константен T псевдоним element)
{
	върни m.insert({key, element}).second;
}

шаблон<типово_име T> булев_тип deleteElement(стандартен::vector<T> псевдоним v, size_t pos)
{
	ако(pos е_по_голямо_или_равно_на v.size()) върни грешно;

	v.erase(v.begin() + pos);

	върни вярно;
}

шаблон<типово_име KEY, типово_име T> булев_тип deleteElement(стандартен::unordered_map<KEY, T> псевдоним m,
															 константен KEY псевдоним key)
{
	върни m.erase(key);
}

шаблон<типово_име T> T псевдоним dereferenceElement(константен стандартен::vector<T> псевдоним v,
													типово_име стандартен::vector<T>::iterator it)
{
	върни достъпи_стойността_на it;
}

шаблон<типово_име T> константен T псевдоним dereferenceElement(константен стандартен::vector<T> псевдоним v,
															   типово_име стандартен::vector<T>::const_iterator it)
{
	върни достъпи_стойността_на it;
}

шаблон<типово_име KEY, типово_име T> T псевдоним dereferenceElement(
	константен стандартен::unordered_map<KEY, T> псевдоним m, типово_име стандартен::unordered_map<KEY, T>::iterator it)
{
	върни it->second;
}

шаблон<типово_име KEY, типово_име T> константен T псевдоним
dereferenceElement(константен стандартен::unordered_map<KEY, T> псевдоним m,
				   типово_име стандартен::unordered_map<KEY, T>::const_iterator it)
{
	върни it->second;
}

шаблон<типово_име KEY, типово_име T> T псевдоним dereferenceElement(стандартен::unordered_map<KEY, T> псевдоним m,
																	константен KEY псевдоним key)
{
	върни m.find(key)->second;
}

шаблон<типово_име KEY, типово_име T> константен T псевдоним
dereferenceElement(константен стандартен::unordered_map<KEY, T> псевдоним m, константен KEY псевдоним key)
{
	върни m.find(key)->second;
}

шаблон<типово_име T> булев_тип hasValidRecords(константен стандартен::unordered_map<std::string, T> псевдоним m)
{
	ако(m.find("INVALID") не_е_равно_на m.end() и m.size() е_равно_на 1) върни грешно;

	върни m.size();
}

шаблон<типово_име T> булев_тип hasValidRecords(константен стандартен::unordered_map<size_t, T> псевдоним m)
{
	ако(m.find(0) не_е_равно_на m.end() и m.size() е_равно_на 1) върни false;

	върни m.size();
}
