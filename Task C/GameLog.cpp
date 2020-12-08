#include "GameLog.h"

void GameLog::showLog() {
	system("CLS");
	SetConsoleTextAttribute(con, 15);
	cout << "+-------------< ";
	SetConsoleTextAttribute(con, 12);
	cout << "INVISIBLE ADVENTURE";
	SetConsoleTextAttribute(con, 15);
	cout << " >-------------+" << endl;
	if (gLog.size() > 10) {
		vector<string> shortLog(gLog.end() - 10, gLog.end());
		for (auto const& v : shortLog) {
			if (v.rfind("[GAME]", 0) == 0) SetConsoleTextAttribute(con, 13);
			if (v.rfind("[ENEMY]", 0) == 0) SetConsoleTextAttribute(con, 12);
			if (v.rfind("[PLAYER]", 0) == 0) SetConsoleTextAttribute(con, 10);
			if (v.rfind("[GOAL]", 0) == 0) SetConsoleTextAttribute(con, 14);
			cout << v << endl;
		}
	}
	else {
		for (auto const& v : gLog) {
			if (v.rfind("[GAME]",0) == 0) SetConsoleTextAttribute(con, 13);
			if (v.rfind("[ENEMY]", 0) == 0) SetConsoleTextAttribute(con, 12);
			if (v.rfind("[PLAYER]", 0) == 0) SetConsoleTextAttribute(con, 10);
			if (v.rfind("[GOAL]", 0) == 0) SetConsoleTextAttribute(con, 14);
			cout << v << endl;
		}
	}
}

void GameLog::showLogFull() {
	system("CLS");
	SetConsoleTextAttribute(con, 15);
	cout << "+-------------< ";
	SetConsoleTextAttribute(con, 12);
	cout << "INVISIBLE ADVENTURE";
	SetConsoleTextAttribute(con, 15);
	cout << " >-------------+" << endl;
	for (auto const& v : gLog) {
		if (v.rfind("[GAME]", 0) == 0) SetConsoleTextAttribute(con, 13);
		if (v.rfind("[ENEMY]", 0) == 0) SetConsoleTextAttribute(con, 12);
		if (v.rfind("[PLAYER]", 0) == 0) SetConsoleTextAttribute(con, 10);
		if (v.rfind("[GOAL]", 0) == 0) SetConsoleTextAttribute(con, 14);
		cout << v << endl;
	}
}

void GameLog::Log(Type t, string s) {
	bool logged = false;
	switch (t) {
	case GAME:
		gLog.push_back("[GAME] " + s);
		logged = true;
		break;
	case ENEMY:
		gLog.push_back("[ENEMY] " + s);
		logged = true;
		break;
	case PLAYER:
		gLog.push_back("[PLAYER] " + s);
		logged = true;
		break;
	case GOAL:
		gLog.push_back("[GOAL] " + s);
		logged = true;
		break;
	default:
		break;
	}
	showLog();
}