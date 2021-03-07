#include "pch.h"
#include "CppUnitTest.h"
#include "../error-by-night/file_io.h"

#include <sstream>
#include <vector>
#include <iostream>

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

			inputStream << "dasd4213213@1!";
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
}
