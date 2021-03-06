#pragma once

#include "structures.h"

void menuDriverMain(std::vector<SCHOOL> &schools);
bool menuMain(std::vector<SCHOOL> &schools);

void selectSchool(std::vector<SCHOOL> &schools);
void listSchools(const std::vector<SCHOOL> &schools);
void menuRestore(std::vector<SCHOOL> &schools);
void menuStore(const std::vector<SCHOOL> &schools);

void menuDriverSchool(SCHOOL &school);
bool menuSchool(SCHOOL &school);

void menuEditName(SCHOOL &school);
void menuEditCity(SCHOOL &school);
void menuEditAddress(SCHOOL &school);

bool menuDriverTeacher(TEACHER &teacher);
bool menuTeacher(TEACHER &teacher);

void menuEditFirstName(TEACHER &teacher);
void menuEditLastName(TEACHER &teacher);
void menuEditEmail(TEACHER &teacher);

bool menuDriverStudent(STUDENT &student);
bool menuStudent(STUDENT &student);

void menuEditFirstName(STUDENT &student);
void menuEditLastName(STUDENT &student);
void menuEditEmail(STUDENT &student);
