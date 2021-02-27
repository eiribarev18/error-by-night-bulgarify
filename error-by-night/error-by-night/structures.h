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

	bool restore(std::ifstream &file);
	void store(std::ofstream &file) const;
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
	void store(std::ofstream &file) const;
};

struct TEAM {
	std::string name;
	std::string description;
	std::string setupDate;
	std::vector<TEAM_MEMBER> members;
	STATUS status;
	std::string project;

	bool restore(std::ifstream &file);
	void store(std::ofstream &file) const;

	std::vector<std::string> getMembers() const;
};

struct PROJECT {
	std::string name;
	std::string description;
	std::vector<size_t> teams;
	STATUS status;

	bool restore(std::ifstream &file);
	void store(std::ofstream &file) const;
};

struct SCHOOL {
	std::string name;
	std::string city;
	std::string address;
	std::unordered_map<std::string, STUDENT> students;
	std::unordered_map<std::string, TEACHER> teachers;
	std::unordered_map<size_t, TEAM> teams;
	std::unordered_map<std::string, PROJECT> projects;

	bool restore(std::ifstream &file);
	void store(std::ofstream &file) const;

	std::vector<std::string> getTeachersWithoutTeam() const;

	bool addStudent(const STUDENT &student, const std::string &username);
	bool deleteStudent(const std::string &username);
	bool addTeacher(const TEACHER &teacher, const std::string &username);
	bool deleteTeacher(const std::string &username);
	bool addTeam(const TEAM &team, size_t id);
	bool deleteTeam(size_t id);
	bool addProject(const PROJECT &project, const std::string &id);
	bool deleteProject(const std::string &id);
};
