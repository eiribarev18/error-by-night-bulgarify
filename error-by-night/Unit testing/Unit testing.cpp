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
}
