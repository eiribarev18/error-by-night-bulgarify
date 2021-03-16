#include "pch.h"
#include "../error-by-night/console_io.h"
#include "../error-by-night/data_manip.h"
#include "../error-by-night/file_io.h"
#include "CppUnitTest.h"


#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Unittesting
{
	TEST_CLASS(test_getUnsignedNumber)
	{
	public:
		
		TEST_METHOD(mustGetValidEnteredNumber)
		{
			stringstream inputStream;
			unsigned num;

			inputStream << 15;
			try {
				getUnsignedNumber(inputStream, num);
			}
			catch (...) {
				Assert::Fail(L"Unexpected exception thrown");
			}
			
			Assert::AreEqual(15u, num);
		} 

		TEST_METHOD(mustThrowWhenNotUnsignedNumber)
		{
			stringstream inputStream;
			unsigned num;

			inputStream << "4x2";
			try {
				getUnsignedNumber(inputStream, num);
			}
			catch (runtime_error &e) {
				if (strcmp(e.what(), "Non-digit character encountered")) {
					Assert::Fail(L"Unexpected message");
				}
				return;
			}
			catch (...) {
				Assert::Fail(L"Unexpected exception type");

			}

			Assert::Fail(L"No exception thrown");
		}

	};

	TEST_CLASS(test_addingElement)
	{
		public :

			TEST_METHOD(mustReturnTrueWhenElementIsCorrectlyAdd)
			{
			
				vector<int> a;
				int element = 22;
				size_t size1 = a.size();
				
				bool returnStatus=addElement(a, element);
				size_t size2 = a.size();
					
				Assert::AreEqual(true, returnStatus,L"The functions had not add the element");
				Assert::AreEqual(size1 + 1, size2, L"Vector size has not changed");
				Assert::AreEqual(element, *find(a.begin(),a.end(),element), L"The element entered isn't correct");
			
			}

			TEST_METHOD(mustReturnFalseIfTheElementAlreadyExcist)
			{
			
				vector<int> a = {22};
				int element = 22;
				size_t size1 = a.size();
				
				bool returnStatus=addElement(a, element);
				size_t size2 = a.size();
					
				Assert::AreEqual(false, returnStatus,L"The functions should have failed");
				Assert::AreEqual(size1, size2, L"Vector size shouldn't have changed");
			
			}

	};

	TEST_CLASS(test_menuAddAdditionalPrep_school) 
	{
		TEST_METHOD(mustAddInvalidStudent) 
		{
			SCHOOL school;
			STUDENT invalidStudent = {"", "", "",0,0};
			menuAddAdditionalPrep(school);
			Assert::AreEqual(invalidStudent.firstName, school.students.begin()->second.firstName);
			Assert::AreEqual(invalidStudent.lastName, school.students.begin()->second.lastName);
			Assert::AreEqual(invalidStudent.email, school.students.begin()->second.email);
			Assert::AreEqual(invalidStudent.grade, school.students.begin()->second.grade);
			Assert::AreEqual(invalidStudent.classLetter, school.students.begin()->second.classLetter);
		}

		TEST_METHOD(mustAddInvalidTeacher)
		{
			SCHOOL school;
			TEACHER invalidTeacher = {"", "", "", {}};
			menuAddAdditionalPrep(school);
			Assert::AreEqual(invalidTeacher.firstName, school.teachers.begin()->second.firstName);
			Assert::AreEqual(invalidTeacher.lastName, school.teachers.begin()->second.lastName);
			Assert::AreEqual(invalidTeacher.email, school.teachers.begin()->second.email);
			Assert::AreEqual(invalidTeacher.teams.size(), school.teachers.begin()->second.teams.size());
		
		}

		TEST_METHOD(mustAddInvalidTeam)
		{
			SCHOOL school;
			TEAM invalidTeam = {"", "", "", {}, STATUS::ARCHIVED, "INVALID"};
			menuAddAdditionalPrep(school);
			Assert::AreEqual(invalidTeam.name, school.teams.begin()->second.name);
			Assert::AreEqual(invalidTeam.description, school.teams.begin()->second.description);
			Assert::AreEqual(invalidTeam.setupDate, school.teams.begin()->second.setupDate);
			Assert::AreEqual(invalidTeam.members.size(), school.teams.begin()->second.members.size());
			Assert::AreEqual((int)invalidTeam.status, (int)school.teams.begin()->second.status);
			Assert::AreEqual(invalidTeam.project, school.teams.begin()->second.project);
		}

		TEST_METHOD(mustAddInvalidProject)
		{
			SCHOOL school;
			PROJECT invalidProject = {"", "", {}, STATUS::ARCHIVED};
			menuAddAdditionalPrep(school);
			Assert::AreEqual(invalidProject.name, school.projects.begin()->second.name);
			Assert::AreEqual(invalidProject.description, school.projects.begin()->second.description);
			Assert::AreEqual(invalidProject.teams.size(), school.projects.begin()->second.teams.size());
			Assert::AreEqual((int)invalidProject.status, (int)school.projects.begin()->second.status);
			
		}
	};
	TEST_CLASS(test_menuAddAdditionalPrep_team) 
	{
		TEST_METHOD(mustSetValidTime) 
		{
			TEAM team1;

			char *tempBuffer = new char[sizeof("YYYY-MM-DD")];
			time_t currTime;
			tm tm_;
			menuAddAdditionalPrep(team1);
			time(&currTime);
			localtime_s(&tm_, &currTime);

			strftime(tempBuffer, sizeof("YYYY-MM-DD"), "%F", &tm_);
			Assert::AreEqual((string)tempBuffer, team1.setupDate);
			delete[] tempBuffer;
			
		}

		TEST_METHOD(mustSetInvalidProject)
		{
			TEAM team1;
			menuAddAdditionalPrep(team1);
			Assert::AreEqual((string)"INVALID",team1.project);
		}

		TEST_METHOD(mustSetInvalidStudent)
		{
			TEAM_MEMBER member;
			menuAddAdditionalPrep(member);
			Assert::AreEqual((string) "INVALID", member.username);
		}
	};
	TEST_CLASS(test_isValidKey)
	{
		TEST_METHOD(mustReturnTrueIfTheValueIsNotZero) 
		{
			size_t a=1;
			Assert::AreEqual(true,isValidKey(a));
		}

		TEST_METHOD(mustReturnTrueIfTheValueIsZero)
		{
			size_t a = 0;
			Assert::AreEqual(false, isValidKey(a));
		}

		TEST_METHOD(mustReturnTrueIfTheValueIstNotINVALID)
		{
			string a = "ala bala";
			Assert::AreEqual(true, isValidKey(a));
		}

		TEST_METHOD(mustReturnFalseIfTheValueIsINVALID)
		{
			string a = "INVALID";
			Assert::AreEqual(false, isValidKey(a));
		}
	};

	TEST_CLASS(test_hasValidRecords) 
	{
		TEST_METHOD(mustReturnFalseWhenTheOnlyRecordIsINVALID) 
		{
			unordered_map<string,int>a;
			a.insert({"INVALID",4});
			Assert::AreEqual(false, hasValidRecords(a));
		}

		TEST_METHOD(mustReturnFalseWhenTheMapIsEmpty_string)
		{
			unordered_map<string, int> a;
		
			Assert::AreEqual(false, hasValidRecords(a));
		}

		TEST_METHOD(mustReturnTrueWhenTheAreValidRecords_string)
		{
			unordered_map<string, int> a;
			a.insert({"INVALID", 4});
			a.insert({"cherven portokal", 4});
			Assert::AreEqual(true, hasValidRecords(a));
		}

		TEST_METHOD(mustReturnFalseWhenTheOnlyRecordIsZero)
		{
			unordered_map<size_t, int> a;
			a.insert({0, 6});
			Assert::AreEqual(false, hasValidRecords(a));
		}

		TEST_METHOD(mustReturnFalseWhenTheMapIsEmpty_size_t)
		{
			unordered_map<size_t, int> a;
			Assert::AreEqual(false, hasValidRecords(a));
		}

		TEST_METHOD(mustReturnTrueWhenTheRecordsAreValid_size_t)
		{
			unordered_map<size_t, int> a;
			a.insert({0, 6});
			a.insert({2, 6});
			Assert::AreEqual(true, hasValidRecords(a));
		}
	};

	TEST_CLASS(test_toString_STATUS) 
	{
		TEST_METHOD(mustGetActiveStatus) 
		{
			STATUS statusActive = STATUS::ACTIVE;
			Assert::AreEqual((string) "ACTIVE", toString(statusActive));
		} 
		TEST_METHOD(mustGetArchivedStatus)
		{
			STATUS statusArchived = STATUS::ARCHIVED;
			Assert::AreEqual((string) "ARCHIVED", toString(statusArchived));
		}
	};

	TEST_CLASS(test_toString_ROLE)
	{
		TEST_METHOD(mustGetScrumMasterRole)
		{	
			TEAM_MEMBER::ROLE roleScrum = TEAM_MEMBER::ROLE::SCRUM_MASTER;
			Assert::AreEqual((string) "SCRUM MASTER", toString(roleScrum));
		}
		TEST_METHOD(mustGetQARole)
		{
			TEAM_MEMBER::ROLE roleQa = TEAM_MEMBER::ROLE::QA_ENGINEER;
			Assert::AreEqual((string) "QA ENGINEER", toString(roleQa));
		}
		TEST_METHOD(mustGetDevBackEndRole)
		{
			TEAM_MEMBER::ROLE roleBackEnd = TEAM_MEMBER::ROLE::DEV_BACKEND;
			Assert::AreEqual((string) "BACKEND DEV", toString(roleBackEnd));
		}
		TEST_METHOD(mustGetDevFrontEndRole)
		{
			TEAM_MEMBER::ROLE roleFrontEnd = TEAM_MEMBER::ROLE::DEV_FRONTEND;
			Assert::AreEqual((string) "FRONTEND DEV", toString(roleFrontEnd));
		}
	};
	}
