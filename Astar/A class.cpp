#include "stdafx.h"

Astar::Queue* Astar::Queue::ptrHeaderQueue = NULL;
Astar::Map** Astar::_map = NULL;
bool Astar::_isResult = false;
int** Astar::_result = NULL;
//bool Astar::Logic::_result = false;
int Astar::_x = 0;
int Astar::_y = 0;
int Astar::_finishX = 0;
int Astar::_finishY = 0;

Astar::Map::Map() {
	isBlack = false;
	accum = 0;
	path = new int*[Astar::_x*Astar::_y];
	for (int i = 0; i < Astar::_x * Astar::_y; i++)
		path[i] = new int[2];
	for (int i = 0; i < Astar::_x * Astar::_y; i++)
		for (int j = 0; j < 2; j++) {
			path[i][j] = -1;
		}
	pathLength = 0;
}

//int Astar::Map::pathLength() {
//	return _pathLength;
//}

void Astar::Map::addPath(int fromX, int fromY) {
	for (int i = 0; i < Astar::_x * Astar::_y; i++) {
		this -> path[i][0] = _map[fromX][fromY].path[i][0];
		this -> path[i][1] = _map[fromX][fromY].path[i][1];
	}
	//this -> path = Astar::_map[x][y].path;
	this -> pathLength = Astar::_map[fromX][fromY].pathLength + 1;
	this -> path[pathLength - 1][0] = fromX;
	this -> path[pathLength - 1][1] = fromY;
	this -> accum = Astar::_map[fromX][fromY].accum + (this -> value);
}

void Astar::_initMap(int** userMap, int x, int y) {
	_map = new Map*[x];
	for (int i = 0; i < x; i++)
		_map[i] = new Map[y];
	for (int i = 0; i < x; i++)
		for (int j = 0; j < y; j++) {
			_map[i][j].value = userMap[i][j];
			_map[i][j].x = i;
			_map[i][j].y = j;
		}

}

bool Astar::Logic::_isBlack(int x, int y) const {
	if (_map[x][y].isBlack)
		return true;
	return false;
}

bool Astar::Logic::_isEveryNodeIsBlack() const {
	for (int i = 0; i < Astar::_x; i++)
		for (int j = 0; j < Astar::_y; j++)
			if (!_isBlack(i,j))
				return false;
	return true;
}

void Astar::_paintBlack(int x, int y) {
	_map[x][y].isBlack = true;
}

bool Astar::Logic::_isResult() const {
	if (Astar::_isResult)
		return true;
	return false;
}

bool Astar::Logic::_isEnqueued(int x, int y) {
	Queue* ptrCurrentQueue = Queue::ptrHeaderQueue;
	while (ptrCurrentQueue != NULL) {
		if (ptrCurrentQueue -> currentPoint.x == x && ptrCurrentQueue -> currentPoint.y == y)
			return true;
		ptrCurrentQueue = ptrCurrentQueue -> next;
	}
	return false;
}

void Astar::_goFirst(int startX, int startY) {
	_paintBlack(startX, startY);
	if (startX == _finishX && startY == _finishY) {
		_map[startX][startY].addPath(startX, startY);
		_result = _map[startX][startY].path;
		_isResult = true;
	}
	else
		_enqueueFrom(startX, startY);
}

void Astar::_goOn() {
	int startX = 0;
	int startY = 0;
	_dequeueAndGetMin(startX, startY);
	//_enqueueFrom(startX, startY);
	_goFirst(startX, startY);
}	   

void Astar::_enqueueFrom(int fromX, int fromY)	 {
	// Обход по направлениям С, СВ, В, ЮВ, Ю ... относительно заданной точки from<X/Y>
	for (int x = -1; x < 2; x++)
		for (int y = -1; y < 2; y ++)
			// Во избежание проверки самой from-вершины
			if (!(x == 0 && y == 0))
				// Проверка на выход за пределы карты
				if ((fromX + x >= 0) && (fromX + x < _x) && (fromY + y >=0) && (fromY + y < _y))
					if (!Logic._isBlack(fromX + x, fromY + y))
						if (!Logic._isEnqueued(fromX + x, fromY + y)) {
						// Если в списке ещё не было элементов
							if (Queue::ptrHeaderQueue == NULL) {
								Queue::ptrHeaderQueue = new Queue(_map[fromX + x][fromY + y]);
								Queue::ptrHeaderQueue -> next = NULL;
								Queue::ptrHeaderQueue -> fromX = fromX;
								Queue::ptrHeaderQueue -> fromY = fromY;
								//Queue::ptrHeaderQueue -> currentPoint.addPath(fromX, fromY);
							}
							// Если в списке уже есть элементы
							else {
								Queue* ptrQueue = Queue::ptrHeaderQueue;
								while (ptrQueue -> next != NULL)
									ptrQueue = ptrQueue -> next;
								// Инициализирует ссылочный член для элемента очереди, ссылка на точку на карте
								ptrQueue -> next = new Queue(_map[fromX + x][fromY + y]);
								ptrQueue = ptrQueue -> next;
								ptrQueue -> next = NULL;
								ptrQueue -> fromX = fromX;
								ptrQueue -> fromY = fromY;
								//ptrQueue -> currentPoint.addPath(fromX,fromY);
							}
					}
}

void Astar::_dequeueAndGetMin(int& minX, int& minY) {
	int minCost = INT_MAX;
	Queue* ptrCurrentQueue;
	Queue* ptrMinCostQueue;
	// 1) Находим минимальную цену (cost = accumPrevious + valueCurrent) ИЛИ (f(x) = g(x) + h(x)), устанавливаем точке currentPoint значения FROM и путь
	if (Queue::ptrHeaderQueue != NULL) {
		ptrCurrentQueue = Queue::ptrHeaderQueue;
		while (ptrCurrentQueue != NULL) {
			if ((ptrCurrentQueue -> currentPoint.value) + (_map[ptrCurrentQueue -> fromX][ptrCurrentQueue -> fromY].accum) <= minCost) {
				ptrMinCostQueue = ptrCurrentQueue;
				// f(x)	=	   				g(x)				  +									h(x)
				minCost = (ptrCurrentQueue -> currentPoint.value) + (_map[ptrCurrentQueue -> fromX][ptrCurrentQueue -> fromY].accum);
			}
			ptrCurrentQueue = ptrCurrentQueue -> next;
		}
		ptrMinCostQueue -> currentPoint.addPath(ptrMinCostQueue -> fromX, ptrMinCostQueue -> fromY);
		ptrMinCostQueue -> currentPoint.accum = minCost;

		// 2) Устанавливаем переданные по ссылкам значения minX и minY
		minX = ptrMinCostQueue -> currentPoint.x;
		minY = ptrMinCostQueue -> currentPoint.y;

		// 3) Удаляем клетку из очереди
		// Если минимальное значение - заголовок
		if (ptrMinCostQueue == Queue::ptrHeaderQueue)
			Queue::ptrHeaderQueue = Queue::ptrHeaderQueue -> next;
		// В противном случае обход начинается сначала
		else {
			ptrCurrentQueue = Queue::ptrHeaderQueue;
			while (ptrCurrentQueue -> next != ptrMinCostQueue) {
				ptrCurrentQueue = ptrCurrentQueue -> next;
			}
			ptrCurrentQueue -> next = ptrMinCostQueue -> next;
		}
		delete ptrMinCostQueue;
	}

}

int** Astar::go(int** userMap, unsigned int mapX, unsigned int mapY, unsigned int startX, unsigned int startY, unsigned int finishX, unsigned int finishY) {
	startX = startX % mapX;
	startY = startY % mapY;
	finishX = finishX % mapY;
	finishY = finishY % mapY;
	_finishX = finishX;
	_finishY = finishY;
	_x = mapX;
	_y = mapY;
	//Init._initAll();
	_initMap(userMap, mapX, mapY);
	_initQueue();
	_initResult();
	
	if (userMap != NULL && mapX > 0 && mapY > 0) {
		_goFirst(startX, startY);
		while (!(Logic._isResult() || Logic._isEveryNodeIsBlack()))
			_goOn();
	}
	return _result;
}

void Astar::_initQueue() {
	Queue* ptrCurrentQueue = Queue::ptrHeaderQueue;
	while (Queue::ptrHeaderQueue != NULL) {
		ptrCurrentQueue = Queue::ptrHeaderQueue -> next;
		delete Queue::ptrHeaderQueue;
		Queue::ptrHeaderQueue = ptrCurrentQueue;
	}
}

void Astar::_initResult() {
	_isResult = false;
	int size;
	if (_result != 0) {
		size = sizeof (*_result) / sizeof (**_result);
		for (int i = 0; i < size; i++)
			delete [] _result [2];
	}
}