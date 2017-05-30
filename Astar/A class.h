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
		// Äîáàâëÿåò ïóòü, óâåëè÷èâàåò accum íà âåëè÷èíó _map[fromX,fromY].accum + this -> value
		void addPath(int fromX, int fromY);
		Map();
	};
	static Map** _map;
	static int _x;			// Øèðèíà êàðòû
	static int _y;			// Âûñîòà êàðòû
	static int** _result;	// Ìàññèâ ïóòè, {{x, y}, {x, y}, ...}
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
		// Åñëè óêàçàííàÿ êëåòêà óæå ïðîéäåíà
		bool _isBlack(int x, int y) const;
		// Åñëè âñÿ êàðòà óæå ïðîñìîòðåíà
		bool _isEveryNodeIsBlack() const;
		// Åñëè åñòü ðåçóëüòàò
		bool _isResult() const;
		// Åñëè âåðøèíà ñ òàêèìè êîîðäèíàòàìè óæå åñòü â î÷åðåäè
		bool _isEnqueued(int x, int y);
	}Logic;

	// Ïîìåùàåò â î÷åðåäü âñå êëåòêè, ñìåæíûå ñ çàäàííûìè êîîðäèíàòàìè 
	void _enqueueFrom(int fromX, int fromY);
	// Âûáèðàåò èç î÷åðåäè êëåòêó ñ ìèíèìàëüíîé ñòîèìîñòüþ, óñòàíàâëèâàåò ïåðåäàííûå ïàðàìåòðû è óäàëÿåò óêàçàííóþ êëåòêó èç î÷åðåäè
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
	
	bool printLastTrack() {return true;} // TODO: remove that mock!

	int** go(int** userMap, unsigned int mapX, unsigned int mapY, unsigned int startX, unsigned int startY, unsigned int finishX, unsigned int finishY);
};
