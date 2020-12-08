#include <iostream>
#include <vector>
#include <Windows.h>
using namespace std;

class GameLog {
	HANDLE con = GetStdHandle(STD_OUTPUT_HANDLE);


public:
	enum Type { GAME, ENEMY, PLAYER, GOAL };
	vector<string> gLog;
	void showLog();
	void showLogFull();
	void Log(Type t, string s);
};