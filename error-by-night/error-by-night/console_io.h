#pragma once

#include "structures.h"

void menuDriverMain(std::vector<SCHOOL> &schools);

bool menuMain(std::vector<SCHOOL> &schools);
void menuRestore(std::vector<SCHOOL> &schools);
void menuStore(const std::vector<SCHOOL> &schools);

bool menuSchool(SCHOOL &school);

void menuEditName(SCHOOL &school);
void menuEditCity(SCHOOL &school);
void menuEditAddress(SCHOOL &school);

bool menuTeacher(TEACHER &teacher);

void menuEditFirstName(TEACHER &teacher);
void menuEditLastName(TEACHER &teacher);
void menuEditEmail(TEACHER &teacher);

bool menuStudent(STUDENT &student);

void menuEditFirstName(STUDENT &student);
void menuEditLastName(STUDENT &student);
void menuEditEmail(STUDENT &student);
