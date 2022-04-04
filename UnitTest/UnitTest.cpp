#include "pch.h"
#include "CppUnitTest.h"
#include "..\Lab12_3.1B\main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Student s[1];
			s[0] = { "Бурачинський", 1, Spec::KN, 4, 4, 4 };
			Assert::AreEqual(4, (int)avgMark(s[0]));
		}
	};
}
