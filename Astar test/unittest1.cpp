#include "stdafx.h"
#include "CppUnitTest.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace Astartest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(IsAbleToPrint) {
			Assert::IsTrue(Astar::getInstance().printLastTrack());
		}
}
