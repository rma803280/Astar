// Astar.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

int** map;

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

int pathLength(int** result) {
	int iter = 0;
	while (result[iter][0] != -1) {
		iter ++;
	}
	return iter;
}

unsigned int _tmain(unsigned int argc, _TCHAR* argv[]){
	init();
	int** result;
	//std::cout << pathLength(Astar::getInstance().go(map, 4, 4, 0, 0, 0, 3));
	/*int size = sizeof(*result) / sizeof(**result);
	std::cout << size << std::endl;*/
	//int iter = 0;
	result = Astar::getInstance().go(map, 4, 4, 0, 0, 3, 3);
	//result = Astar::getInstance().go(map, 4, 4, 0, 0, 0, 0);
	std::cout << " x	y" << std::endl << std::endl;
	for (int i = 0; i < 16; i++){
		if ((result[i][0] != -1) || (result[i][1]) != -1)
		std::cout << " " << result[i][0] <<"	" << result[i][1] << std::endl;
	}
	
	system("Pause");
}

