#pragma once

#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

enum class STATUS {
	ACTIVE,
	ARCHIVED
};

struct STUDENT {
	std::string firstName;
	std::string lastName;
	std::string email;
	unsigned grade;
	char classLetter;

	bool restore(std::istream &file);
	void store(std::ostream &file) const;
};

struct TEACHER {
	std::string firstName;
	std::string lastName;
	std::string email;
	std::vector<size_t> teams;

	bool restore(std::istream &file);
	void store(std::ostream &file) const;
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

struct TEAM {
	std::string name;
	std::string description;
	std::string setupDate;
	std::vector<TEAM_MEMBER> members;
	STATUS status;
	std::string project;

	bool restore(std::istream &file);
	void store(std::ostream &file) const;

	std::vector<std::string> getMembers() const;
};

struct PROJECT {
	std::string name;
	std::string description;
	std::vector<size_t> teams;
	STATUS status;

	bool restore(std::istream &file);
	void store(std::ostream &file) const;
};

struct SCHOOL {
	std::string name;
	std::string city;
	std::string address;
	std::unordered_map<std::string, STUDENT> students;
	std::unordered_map<std::string, TEACHER> teachers;
	std::unordered_map<size_t, TEAM> teams;
	std::unordered_map<std::string, PROJECT> projects;

	bool restore(std::istream &file);
	void store(std::ostream &file) const;

	std::vector<std::string> getTeachersWithoutTeam() const;
};

bool operator==(const TEAM_MEMBER &lhs, const TEAM_MEMBER &rhs);
