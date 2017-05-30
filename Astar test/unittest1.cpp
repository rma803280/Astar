#include "stdafx.h"
#include "CppUnitTest.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

int** map;

int pathLength(int** result) {
	int iter = 0;
	while (result[iter][0] != -1) {
		iter ++;
	}
	return iter;
}

/*
Y
^
|8	8	8	1
|4	3	8	2
|5	4	3	5
|6	5	5	5
|-------------> X
*/
void init() {
	map = new int*[4];
	for (int i = 0; i < 4; i++)
		map[i] = new int[4];
		map[0][0] = 6;
		map[0][1] = 5;
		map[0][2] = 4;
		map[0][3] = 8;
		map[1][0] = 5;
		map[1][1] = 4;
		map[1][2] = 3;
		map[1][3] = 8;
		map[2][0] = 5;
		map[2][1] = 3;
		map[2][2] = 8;
		map[2][3] = 8;
		map[3][0] = 5;
		map[3][1] = 5;
		map[3][2] = 2;
		map[3][3] = 1;
}

namespace Astartest
{		
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(IsAbleToPrint) {
			Assert::IsTrue(Astar::getInstance().printLastTrack());
		}
	};
}
