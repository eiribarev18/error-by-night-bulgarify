#pragma once
#include <string>
#include <vector>
#include <unordered_map>

struct STUDENT {
	std::string firstName;
	std::string lastName;
	std::string email;
	int grade;
	char classLetter;
};

struct TEAM {
	std::string name;
	std::string description;
	std::string setupDate;
	std::vector <std::string> memberUsernames;
};

struct TEACHER {
	std::string firstName;
	std::string lastName;
	std::string email;
	std::vector <int> teamIDs;
};

struct SCHOOL {
	std::string name;
	std::string city;
	std::string address;
	std::unordered_map <int, TEAM> teams;
	std::unordered_map <std::string, STUDENT> students;
	std::unordered_map <std::string, TEACHER> teacher;
};