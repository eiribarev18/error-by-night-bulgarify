#pragma once

#include "structures.h"

void menuDriverMain(std::vector<SCHOOL> &schools);

bool menuMain(std::vector<SCHOOL> &schools);
void menuRestore(std::vector<SCHOOL> &schools);
void menuStore(const std::vector<SCHOOL> &schools);
void menuEditName(SCHOOL &schools);
void menuEditCity(SCHOOL &schools);
void menuEditAddress(SCHOOL &schools);
void menuEditFirstName(TEACHER &teacher);
void menuEditLastName(TEACHER &teacher);
void menuEditEmail(TEACHER &teacher);
