#pragma once
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

struct STUDENT {
	std::string firstName;
	std::string lastName;
	std::string email;
	unsigned grade;
	char classLetter;

	bool restore(std::ifstream &file);
};

struct TEAM_MEMBER {
	enum ROLE {
		SCRUM_MASTER,
		QA_ENGINEER,
		DEV_BACKEND,
		DEV_FRONTEND
	};

	std::string username;
	ROLE role;
};

struct TEACHER {
	std::string firstName;
	std::string lastName;
	std::string email;
	std::vector<int> teamIDs;

	bool restore(std::ifstream &file);
};

struct TEAM {
	std::string name;
	std::string description;
	std::string setupDate;
	std::vector<TEAM_MEMBER> members;

	bool restore(std::ifstream &file);
};

struct SCHOOL {
	std::string name;
	std::string city;
	std::string address;
	std::unordered_map<std::string, STUDENT> students;
	std::unordered_map<std::string, TEACHER> teachers;
	std::unordered_map<size_t, TEAM> teams;

	bool restore(std::ifstream &file);
};
