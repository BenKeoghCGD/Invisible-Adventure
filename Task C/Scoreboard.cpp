#include "Scoreboard.h"
#include <sstream>
using namespace std;


void Scoreboard::Submit(string name, int score) {
	ofstream f_Out("scores.csv", ios::app | ios::out);
	f_Out << name << "," << score << endl;
	f_Out.close();
}

vector<pair<string, int>> Scoreboard::Read() {
	vector<pair<string, int>> result;
	ifstream f_In("scores.csv");
	string line, name;
	int score;
	if (f_In.good()) {
		while (!f_In.eof()) {
			f_In >> line;
			int pos = line.find(",");
			name = line.substr(0, pos);
			score = stoi(line.substr(pos + 1, line.length() - (pos + 1)));
			result.push_back({ name,score });
		}
		result.pop_back();
	}
	return result;
}