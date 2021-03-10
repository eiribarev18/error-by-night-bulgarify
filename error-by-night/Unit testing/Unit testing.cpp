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
			catch (exception &e) {
				Assert::Fail(L"Unexpected exception thrown");
			}
			
			Assert::AreEqual(15u, num);
		} 

		TEST_METHOD(mustThrowWhenNotUnsignedNumber)
		{
			stringstream inputStream;
			unsigned num;

			inputStream << "4";
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
				int element;
				int size1 = a.size();
				
				bool returnStatus=addElement(a, element);
				int size2 = a.size();
					
				Assert::AreEqual(true, returnStatus,L"The functions had not add the element");
				Assert::AreEqual(size1 + 1, size2, L"Vector size has not changed");
				Assert::AreEqual(element, *find(a.begin(),a.end(),element), L"The element entered isn't correct");
			
			}

			TEST_METHOD(mustReturnFalseIfTheElementAlreadyExcist)
			{
			
				vector<int> a;
				int element;
				int size1 = a.size();
				
				bool returnStatus=addElement(a, element);
				int size2 = a.size();
					
				Assert::AreEqual(false, returnStatus,L"The functions should have failed");
				Assert::AreEqual(size1, size2, L"Vector size shouldn't have changed");
			
			}

	};
}
