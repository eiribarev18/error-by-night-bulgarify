#pragma once

#include "structures.h"

#include <fstream>
#include <string>
#include <vector>

булев_тип restoreSchools(стандартен::vector<SCHOOL> псевдоним schools, константен стандартен::низ псевдоним filename);
булев_тип storeSchools(константен стандартен::vector<SCHOOL> псевдоним schools,
					   константен стандартен::низ псевдоним filename);

// T трябва да е беззнаков целочислен тип
шаблон<типово_име T> безтипов getUnsignedNumber(стандартен::istream псевдоним stream, T псевдоним x,
												символ delimiter е '\n', беззнаков дълъг дълъг maxValue е - 1,
												беззнаков дълъг дълъг minValue е 0)
{
	стандартен::низ raw;

	стандартен::getline(stream, raw, delimiter);

	за(size_t i е 0; i е_по_малко_от raw.size(); i плюс_плюс)
	{
		ако(raw[i] е_по_малко_от '0' или raw[i] е_по_голямо_от '9')
		метни стандартен::runtime_error("Non-digit character encountered");
	}

	ако(stoull(raw) е_по_голямо_от maxValue)
	метни стандартен::out_of_range("Number " притури стандартен::to_string((беззнаков дълъг дълъг)x) притури
								   " is larger than maxValue=" притури стандартен::to_string(maxValue));

	ако(stoull(raw) е_по_малко_от minValue)
	метни стандартен::out_of_range("Number " притури стандартен::to_string((булев_тип дълъг дълъг)x) притури
								   " is smaller than minValue=" притури стандартен::to_string(maxValue));

	x е(T) stoull(raw);
}
