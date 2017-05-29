class Astar {
private:
	struct Map {
		int pathLength;
		int x;
		int y;
		int value;
		int accum;
		bool isBlack;
		int** path;
		//int pathLength();
		// ƒобавл€ет путь, увеличивает accum на величину _map[fromX,fromY].accum + this -> value
		void addPath(int fromX, int fromY);
		Map();
	};
	static Map** _map;
	static int _x;			// Ўирина карты
	static int _y;			// ¬ысота карты
	static int** _result;	// ћассив пути, {{x, y}, {x, y}, ...}
	static int _finishX;
	static int _finishY;
	static bool _isResult;

	void _initResult();
	void _initMap();
	void _initQueue();

	struct Queue {
		static Queue* ptrHeaderQueue;
		Queue* next;
		Map& currentPoint;
		int fromX;
		int fromY;
		Queue() : currentPoint(Astar::_map[0][0]) {}
		Queue(Map& point) : currentPoint(point) {}
	};

	struct Logic {
		// ≈сли указанна€ клетка уже пройдена
		bool _isBlack(int x, int y) const;
		// ≈сли вс€ карта уже просмотрена
		bool _isEveryNodeIsBlack() const;
		// ≈сли есть результат
		bool _isResult() const;
		// ≈сли вершина с такими координатами уже есть в очереди
		bool _isEnqueued(int x, int y);
	}Logic;

	// ѕомещает в очередь все клетки, смежные с заданными координатами 
	void _enqueueFrom(int fromX, int fromY);
	// ¬ыбирает из очереди клетку с минимальной стоимостью, устанавливает переданные параметры и удал€ет указанную клетку из очереди
	void _dequeueAndGetMin(int& minX, int& minY);
	void _paintBlack(int x, int y);
	void _goFirst(int startX, int startY);
	void _goOn();
	void _initMap(int** userMap, int x, int y);

	Astar() {};
	Astar(const Astar& root) {};
	Astar operator=(const Astar& root) {};
public:
	static Astar& getInstance() {
		static Astar instance;
		return instance;
	}

	int** go(int** userMap, unsigned int mapX, unsigned int mapY, unsigned int startX, unsigned int startY, unsigned int finishX, unsigned int finishY);
};
