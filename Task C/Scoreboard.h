#include <fstream>
#include <vector>
using namespace std;

class Scoreboard {
public:
	void Submit(string name, int score);
	vector<pair<string, int>> Read();
};