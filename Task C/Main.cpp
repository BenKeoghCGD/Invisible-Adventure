#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>
#include <shellapi.h>
#include "Configuration.h"
#include "GameLog.h"
#include "Scoreboard.h"
#include "EmojiLibrary.cpp"
#include "Player.h"
#include "Enemy.h"
#include <algorithm>
#include "Goal.h"
using namespace std;

const int GRID_X = 20, GRID_Y = 20;

// Variables
Configuration conf;
GameLog logger;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
bool defaultSet = false, gameComplete = false;
Player p;
vector<Enemy> Enemies;
Goal g;
Scoreboard s;

// Game Variables
char grid[GRID_Y][GRID_X];
int max_enemies;

// Declare Functions
void o_Show();
void init();
void g_Begin();
void g_Initialize();
void show_Map();
void win();
void lose();
void e_Move();
void checkHealth(int amount);
void s_Show();

bool sortbysecdesc(const pair<string, int>& a,
	const pair<string, int>& b)
{
	return a.second < b.second;
}


// INVISIBLE ADVENTURE
int main() {
	if (!defaultSet) init();

	system("CLS");

	SetConsoleTextAttribute(hConsole, 15);
	cout << "+-------------< ";
	SetConsoleTextAttribute(hConsole, 12);
	cout << "INVISIBLE ADVENTURE";
	SetConsoleTextAttribute(hConsole, 15);
	cout << " >-------------+" << endl << "|";
	SetConsoleTextAttribute(hConsole, 10);
	cout << " Welcome to Invisible Adventure! A console-based ";
	SetConsoleTextAttribute(hConsole, 15);
	cout << "|" << endl << "|";
	SetConsoleTextAttribute(hConsole, 10);
	cout << " adventure game where  you traverse a map filled ";
	SetConsoleTextAttribute(hConsole, 15);
	cout << "|" << endl << "|";
	SetConsoleTextAttribute(hConsole, 10);
	cout << " with invisible enemies!  find the goal based on ";
	SetConsoleTextAttribute(hConsole, 15);
	cout << "|" << endl << "|";
	SetConsoleTextAttribute(hConsole, 10);
	cout << "  nothing but minor hints and a distance marker  ";
	SetConsoleTextAttribute(hConsole, 15);
	cout << "|" << endl << "+-------------------------------------------------+" << endl << "|";
	SetConsoleTextAttribute(hConsole, 10);
	cout << " Menu:                                           ";
	SetConsoleTextAttribute(hConsole, 15);
	cout << "|" << endl << "|";
	SetConsoleTextAttribute(hConsole, 10);
	cout << " 1 - Begin Game                                  ";
	SetConsoleTextAttribute(hConsole, 15);
	cout << "|" << endl  << "|";
	SetConsoleTextAttribute(hConsole, 10);
	cout << " 2 - Options                                     ";
	SetConsoleTextAttribute(hConsole, 15);
	cout << "|" << endl << "|";
	SetConsoleTextAttribute(hConsole, 10);
	cout << " 3 - View Source Code (GitHub)                   ";
	SetConsoleTextAttribute(hConsole, 15);
	cout << "|" << endl << "|";
	SetConsoleTextAttribute(hConsole, 10);
	cout << " 4 - View Scoreboard                             ";
	SetConsoleTextAttribute(hConsole, 15);
	cout << "|" << endl << "|";
	SetConsoleTextAttribute(hConsole, 10);
	cout << " 5 - Exit Game                                   ";
	SetConsoleTextAttribute(hConsole, 15);
	cout << "|" << endl << "+-------------------------------------------------+" << endl;


	int option;
	SetConsoleTextAttribute(hConsole, 12);
	cout << "\n\nInput Option: ";
	SetConsoleTextAttribute(hConsole, 15);
	cin >> option;

	switch (option) {
	case 1:
		g_Begin();
		break;

	case 2:
		o_Show();
		break;

	case 3:
		ShellExecute(0, 0, L"https://github.com/BenKeoghCGD/invisible-adventure", 0, 0, SW_SHOW);
		break;

	case 4:
		s_Show();
		break;

	case 5:
		return 0;
	
	default:
		main();
		break;
	}

	return 0;
}

void o_Show() {

	system("CLS");

	SetConsoleTextAttribute(hConsole, 15);
	cout << "+-------------< ";
	SetConsoleTextAttribute(hConsole, 12);
	cout << "OPTIONS & CONTROLS";
	SetConsoleTextAttribute(hConsole, 15);
	cout << " >-------------+" << endl;

	for (int i = 0; i < 4; i++) {
		SetConsoleTextAttribute(hConsole, 15);
		cout << "| ";
		SetConsoleTextAttribute(hConsole, 10);
		cout << i << " - " << conf.intToControl(i) << ": " << conf.getControl(i) << endl;
	}
	SetConsoleTextAttribute(hConsole, 15);
	cout << "| ";
	SetConsoleTextAttribute(hConsole, 10);
	cout << "4 - EXIT OPTIONS" << endl;

	SetConsoleTextAttribute(hConsole, 15);
	cout << "+------------------------------------------------+" << endl;

	int option;
	SetConsoleTextAttribute(hConsole, 12);
	cout << "\n\nInput Option: ";
	SetConsoleTextAttribute(hConsole, 15);
	cin >> option;

	if (option == 4) main();
	else if (option > 4 || option < 0) o_Show();
	else {
		system("CLS");
		SetConsoleTextAttribute(hConsole, 10);
		cout << "Editing " << option << ". Previous value: " << conf.getControl(option) << endl;
		char input;
		SetConsoleTextAttribute(hConsole, 12);
		cout << "\n\nInput Option: ";
		SetConsoleTextAttribute(hConsole, 15);
		cin >> input;
		conf.changeControl(option, toupper(input));
		o_Show();
	}
}

void g_Begin() {
	system("CLS");

	SetConsoleTextAttribute(hConsole, 15);
	cout << "+-------------< ";
	SetConsoleTextAttribute(hConsole, 12);
	cout << "DIFFICULTY";
	SetConsoleTextAttribute(hConsole, 15);
	cout << " >-------------+" << endl << "|";
	SetConsoleTextAttribute(hConsole, 10);
	cout << " 0 - EASY "<< endl;
	SetConsoleTextAttribute(hConsole, 15);
	cout << "|";
	SetConsoleTextAttribute(hConsole, 8);
	cout << "     150 HEALTH - 5 ENEMIES" << endl;
	SetConsoleTextAttribute(hConsole, 15);
	cout << "|";
	SetConsoleTextAttribute(hConsole, 10);
	cout << " 1 - INTERMEDIATE" << endl;
	SetConsoleTextAttribute(hConsole, 15);
	cout << "|";
	SetConsoleTextAttribute(hConsole, 8);
	cout << "     100 HEALTH - 10 ENEMIES" << endl;
	SetConsoleTextAttribute(hConsole, 15);
	cout << "|";
	SetConsoleTextAttribute(hConsole, 12);
	cout << "     ENEMIES MOVE ON PLAYER MOVE" << endl;
	SetConsoleTextAttribute(hConsole, 15);
	cout << "|";
	SetConsoleTextAttribute(hConsole, 10);
	cout << " 2 - HARD" << endl;
	SetConsoleTextAttribute(hConsole, 15);
	cout << "|";
	SetConsoleTextAttribute(hConsole, 8);
	cout << "     75 HEALTH - 20 ENEMIES" << endl;
	SetConsoleTextAttribute(hConsole, 15);
	cout << "|";
	SetConsoleTextAttribute(hConsole, 12);
	cout << "     ENEMIES MOVE ON PLAYER MOVE" << endl;
	SetConsoleTextAttribute(hConsole, 15);
	cout << "+-------------------------------------+";

	int option;
	SetConsoleTextAttribute(hConsole, 12);
	cout << "\n\nInput Option: ";
	SetConsoleTextAttribute(hConsole, 15);
	cin >> option;

	cin.ignore();

	switch (option) {
	case 0:
		//EASY
		conf.setSetting(Configuration::MAX_ENEMIES, 5);
		conf.setSetting(Configuration::DAMAGE_CELL, 3);
		conf.setSetting(Configuration::PLAYER_HEALTH, 150);
		conf.setSetting(Configuration::DAMAGE_MOVE, 0);
		conf.setSetting(Configuration::MOVES_TO_GOAL, 5);
		max_enemies = 5;
		break;

	case 1:
		//INTERMEDIATE
		conf.setSetting(Configuration::MAX_ENEMIES, 10);
		conf.setSetting(Configuration::DAMAGE_CELL, 5);
		conf.setSetting(Configuration::PLAYER_HEALTH, 100);
		conf.setSetting(Configuration::DAMAGE_MOVE, 1);
		conf.setSetting(Configuration::MOVES_TO_GOAL, 10);
		max_enemies = 10;
		break;

	case 2:
		//HARD
		conf.setSetting(Configuration::MAX_ENEMIES, 20);
		conf.setSetting(Configuration::DAMAGE_CELL, 7);
		conf.setSetting(Configuration::PLAYER_HEALTH, 75);
		conf.setSetting(Configuration::DAMAGE_MOVE, 3);
		conf.setSetting(Configuration::MOVES_TO_GOAL, 15);
		max_enemies = 20;
		break;
	}

	g_Initialize();
	system("CLS");
	SetConsoleTextAttribute(hConsole, 15);
	cout << "+-------------< ";
	SetConsoleTextAttribute(hConsole, 12);
	cout << "INVISIBLE ADVENTURE";
	SetConsoleTextAttribute(hConsole, 15);
	cout << " >-------------+" << endl;
	logger.Log(GameLog::GAME, "Game Beginning");

	vector<string> logPrevious;
	bool mapPrevious = GetKeyState('M') & 1;
	bool moveUpPrev = false, moveDownPrev = false, moveRightPrev = false, moveLeftPrev = false;

	do {
		bool madeMove = false;
		// VISUAL
		if (logger.gLog.size() != logPrevious.size() || (GetKeyState('M') & 1) != mapPrevious) {
			logger.showLog();
			if(GetKeyState('M') & 1) show_Map();

			logPrevious = logger.gLog;
			mapPrevious = GetKeyState('M') & 1;

			cout << endl << endl;
			SetConsoleTextAttribute(hConsole, 12);
			cout << "HEALTH: " << p.Health() << " | DISTANCE TO GOAL: " << (int)abs(p.position.x - g.position.x) + abs(p.position.y - g.position.y) << " | ENEMIES REMAINING: " << Enemies.size() << " | LIVES: " << p.lives;
		}

		if (GetKeyState(VK_SHIFT) & 1 && GetKeyState('E') & 1) lose();

		// DETECTIONS ((Y, X))
		bool mU = GetKeyState(conf.getControl(0)) & 0x8000, mD = GetKeyState(conf.getControl(1)) & 0x8000, mL = GetKeyState(conf.getControl(2)) & 0x8000, mR = GetKeyState(conf.getControl(3)) & 0x8000;
		if (mU && mU != moveUpPrev) {
			moveUpPrev = mU;
			logger.Log(GameLog::GAME, "MOVE UP");
			madeMove = true;

			if (p.position.y != 0) {
				grid[p.position.y][p.position.x] = '@';
				p.position.y -= 1;
				grid[p.position.y][p.position.x] = 'P';
			}
		}
		else if (!mU && mU != moveUpPrev) moveUpPrev = mU;

		if (mD && mD != moveDownPrev) {
			moveDownPrev = mD;
			logger.Log(GameLog::GAME, "MOVE DOWN");
			madeMove = true;

			if (p.position.y != 19) {
				grid[p.position.y][p.position.x] = '@';
				p.position.y += 1;
				grid[p.position.y][p.position.x] = 'P';
			}
		}
		else if (!mD && mD != moveDownPrev) moveDownPrev = mD;

		if (mL && mL != moveLeftPrev) {
			moveLeftPrev = mL;
			logger.Log(GameLog::GAME, "MOVE LEFT");
			madeMove = true;
			if (p.position.x != 0) {
				grid[p.position.y][p.position.x] = '@';
				p.position.x -= 1;
				grid[p.position.y][p.position.x] = 'P';
			}
		}
		else if (!mL && mL != moveLeftPrev) moveLeftPrev = mL;

		if (mR && mR != moveRightPrev) {
			moveRightPrev = mR;
			logger.Log(GameLog::GAME, "MOVE RIGHT");
			madeMove = true;
			if (p.position.x != 19) {
				grid[p.position.y][p.position.x] = '@';
				p.position.x += 1;
				grid[p.position.y][p.position.x] = 'P';
			}
		}
		else if (!mR && mR != moveRightPrev) moveRightPrev = mR;

		// MOVE ENEMIES!
		if (madeMove) {
			if(conf.getSetting(conf.MAX_ENEMIES) != 5) e_Move();
			if (p.position.x == g.position.x && p.position.y == g.position.y) win();
			else {
				checkHealth(conf.getSetting(Configuration::DAMAGE_MOVE));
				int i = 0;
				for (auto const& v : Enemies) {
					if (p.position.x == v.position.x && p.position.y == v.position.y) {
						checkHealth(conf.getSetting(Configuration::DAMAGE_CELL));
						Enemies.erase(Enemies.begin() + i);
						logger.Log(logger.ENEMY, string("YOU LANDED ON AN ENEMY! (-") + to_string(conf.getSetting(Configuration::DAMAGE_CELL)) + "HP)");
					}
					if ((abs(p.position.x - v.position.x) + abs(p.position.y - v.position.y)) == 1) logger.Log(logger.ENEMY, "YOU ARE ONE SQUARE AWAY FROM AN ENEMY!");

					i++;
				}
			}
		}
	} while (!gameComplete);
}

// Initialize Variables
void init() {
	conf.changeControl(0, 'W');
	conf.changeControl(1, 'S');
	conf.changeControl(2, 'A');
	conf.changeControl(3, 'D');
	defaultSet = true;

	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, 1200, 750, TRUE);
}

void g_Initialize() {
	Enemies.clear();
	// POPULATE GRID
	vector<int> enemy_Positions;
	int player_Position = rand() % 400;

	for (int i = 0; i < max_enemies; i++) {
		int key = rand() % 400;
		if (find(enemy_Positions.begin(), enemy_Positions.end(), key) != enemy_Positions.end()) i--;
		else enemy_Positions.push_back(key);
	}
	if (find(enemy_Positions.begin(), enemy_Positions.end(), player_Position) != enemy_Positions.end()) g_Initialize();

	bool goal_populated = false;

	int i = 0;
	for (int y = 0; y < GRID_Y; y++) {
		for (int x = 0; x < GRID_X; x++) {
			if (find(enemy_Positions.begin(), enemy_Positions.end(), i) != enemy_Positions.end()) {
				grid[y][x] = 'E';
				Enemy e;
				e.position.x = x;
				e.position.y = y;
				Enemies.push_back(e);
			}
			else if (i == player_Position) {
				grid[y][x] = 'P';
				Player pl;
				pl.Health(conf.getSetting(Configuration::Settings::PLAYER_HEALTH));
				pl.position.x = x;
				pl.position.y = y;
				p = pl;
				cout << p.position.x << "," << p.position.y << endl;
			}
			else {
				int distance = abs(p.position.y - y) + abs(p.position.x - x);
				if (distance >= conf.getSetting(Configuration::MOVES_TO_GOAL) && rand() % 100 + 1 == rand() % 100 + 1 && !goal_populated) {
					grid[y][x] = 'G';
					g.position.x = x;
					g.position.y = y;
					goal_populated = true;
				}
				else grid[y][x] = '@';
			}
			i++;
		}
	}
}

void show_Map() {
	SetConsoleTextAttribute(hConsole, 15);
	cout << "\n\n+---------< ";
	SetConsoleTextAttribute(hConsole, 12);
	cout << "ADMINISTRATOR TOOLS";
	SetConsoleTextAttribute(hConsole, 15);
	cout << " >---------+" << endl;
	for (int y = 0; y < GRID_Y; y++) {
		SetConsoleTextAttribute(hConsole, 15);
		cout << "| ";
		for (int x = 0; x < GRID_X; x++) {
			SetConsoleTextAttribute(hConsole, 15);
			if (grid[y][x] == 'E') SetConsoleTextAttribute(hConsole, 12);
			if (grid[y][x] == 'P') SetConsoleTextAttribute(hConsole, 10);
			if (grid[y][x] == 'G') SetConsoleTextAttribute(hConsole, 14);
			cout << grid[y][x] << " ";
		}
		SetConsoleTextAttribute(hConsole, 15);
		cout << "|" << endl;
	}
	SetConsoleTextAttribute(hConsole, 15);
	cout << "+-----------------------------------------+" << endl;


	cout << "\n\n" << p.position.x << "," << p.position.y << endl;
}

void win()
{
	gameComplete = true;
	system("CLS");
	SetConsoleTextAttribute(hConsole, 15);
	cout << "+-------------< ";
	SetConsoleTextAttribute(hConsole, 12);
	cout << "INVISIBLE ADVENTURE";
	SetConsoleTextAttribute(hConsole, 15);
	cout << " >-------------+" << endl << "|";
	SetConsoleTextAttribute(hConsole, 10);
	cout << "  Good golly fearless adventurer! You found the  ";
	SetConsoleTextAttribute(hConsole, 15);
	cout << "|" << endl << "|";
	SetConsoleTextAttribute(hConsole, 10);
	cout << " ancient coin rather quickly, didn't you! You're ";
	SetConsoleTextAttribute(hConsole, 15);
	cout << "|" << endl << "|";
	SetConsoleTextAttribute(hConsole, 10);
	cout << "  going down in the history books this time! be  ";
	SetConsoleTextAttribute(hConsole, 15);
	cout << "|" << endl << "|";
	SetConsoleTextAttribute(hConsole, 10);
	cout << " sure to submit your score to the book of heroes!";
	SetConsoleTextAttribute(hConsole, 15);
	cout << "|" << endl << "+-------------------------------------------------+" << endl;
	SetConsoleTextAttribute(hConsole, 12);
	cout << "\n\nInput Name to Book of Heroes: ";
	SetConsoleTextAttribute(hConsole, 15);

	string name;
	cin >> name;

	/*
		max score:
		health max 100 * 100 = 100
		lives max 3 * 500 = 1500
		moves max 38 * 100 = 380
		enemies max 20 * 200 = 4000

		ALL ENEMIES + 20

		total = 15000
	*/

	int score = (p.Health() * 100) + (p.lives * 500) + ((abs(p.position.x - g.position.x) + abs(p.position.y - g.position.y)) * 100) + ((conf.getSetting(conf.MAX_ENEMIES) - Enemies.size()) * 200) + (Enemies.empty() ? 20 : 0);

	s.Submit(name, score);

	SetConsoleTextAttribute(hConsole, 12);
	cout << "\n\nInputted to Scoreboard: ";
	SetConsoleTextAttribute(hConsole, 10);
	cout << name << " - " << score;

	system("pause");

	main();
}

void lose() {
	gameComplete = true;
	system("CLS");
	SetConsoleTextAttribute(hConsole, 15);
	cout << "+-------------< ";
	SetConsoleTextAttribute(hConsole, 12);
	cout << "INVISIBLE ADVENTURE";
	SetConsoleTextAttribute(hConsole, 15);
	cout << " >-------------+" << endl << "|";
	SetConsoleTextAttribute(hConsole, 10);
	cout << " Sorry friend! Your adventure has come to an end ";
	SetConsoleTextAttribute(hConsole, 15);
	cout << "|" << endl << "|";
	SetConsoleTextAttribute(hConsole, 10);
	cout << " early! Unfortunately, you failed your only task ";
	SetConsoleTextAttribute(hConsole, 15);
	cout << "|" << endl << "|";
	SetConsoleTextAttribute(hConsole, 10);
	cout << " You can always give it another shot! Make sure  ";
	SetConsoleTextAttribute(hConsole, 15);
	cout << "|" << endl << "|";
	SetConsoleTextAttribute(hConsole, 10);
	cout << "   to submit your score to the book of heroes!   ";
	SetConsoleTextAttribute(hConsole, 15);
	cout << "|" << endl << "+-------------------------------------------------+" << endl;
	SetConsoleTextAttribute(hConsole, 12);
	cout << "\n\nInput Name to Book of Heroes: ";
	SetConsoleTextAttribute(hConsole, 15);
	string name;
	getline(cin, name);

	int score = (p.Health() * 100) + (p.lives * 500) + ((abs(p.position.x - g.position.x) + abs(p.position.y - g.position.y)) * 100) + ((conf.getSetting(conf.MAX_ENEMIES) - Enemies.size()) * 200) + (Enemies.empty() ? 20 : 0);

	s.Submit(name, score);

	SetConsoleTextAttribute(hConsole, 12);
	cout << "\n\nInputted to Scoreboard: ";
	SetConsoleTextAttribute(hConsole, 10);
	cout << name << " - " << score;

	system("pause");
	
	main();
}

int prev_enemy;

void e_Move()
{
	int enemy = rand() % Enemies.size();
	if (enemy == prev_enemy) e_Move();
	else {
		prev_enemy = enemy;
		Enemy v = Enemies[enemy];
		bool moved = false;
		do {
			int key = rand() % 20 + 1;
			if (key >= 1 && key <= 5) {
				// UP
				if (grid[v.position.y + 1][v.position.x] == '@') {
					grid[v.position.y + 1][v.position.x] = 'E';
					grid[v.position.y][v.position.x] = '@';
					v.changePosition(v.position.x, v.position.y + 1);
					moved = true;
				}
			}
			if (key >= 6 && key <= 10) {
				// DOWN
				if (grid[v.position.y - 1][v.position.x] == '@') {
					grid[v.position.y - 1][v.position.x] = 'E';
					grid[v.position.y][v.position.x] = '@';
					v.changePosition(v.position.x, v.position.y - 1);
					moved = true;
				}
			}
			if (key >= 11 && key <= 15) {
				// LEFT
				if (grid[v.position.y][v.position.x + 1] == '@') {
					grid[v.position.y][v.position.x + 1] = 'E';
					grid[v.position.y][v.position.x] = '@';
					v.changePosition(v.position.x + 1, v.position.y);
					moved = true;
				}
			}
			if (key >= 16 && key <= 20) {
				// RIGHT
				if (grid[v.position.y][v.position.x - 1] == '@') {
					grid[v.position.y][v.position.x - 1] = 'E';
					grid[v.position.y][v.position.x] = '@';
					v.changePosition(v.position.x - 1, v.position.y);
					moved = true;
				}
			}
		} while (!moved);
	}
	
}

void checkHealth(int amount)
{
	int oldHealth = p.Health();
	if (p.Health() <= 0) {
		logger.Log(logger.PLAYER, "YOU DIED!");
		if (p.lives > 0) {
			p.lives -= 1;
			grid[p.position.y][p.position.x] = '@';
			bool respawned = false;
			do {
				int x = rand() % 20, y = rand() % 20;
				if (grid[y][x] != '@') {
					p.Health(conf.getSetting(Configuration::PLAYER_HEALTH));
					logger.Log(logger.PLAYER, "YOU'VE RESPAWNED!");
					p.position.x = x;
					p.position.y = y;
					grid[y][x] = 'P';
					respawned = true;
				}
			} while (!respawned);
		}
		else lose();
	}
	else {
		p.Health(oldHealth - amount);
		if ((oldHealth - amount) <= 0) checkHealth(0);
	}
}

void s_Show() {
	system("CLS");

	SetConsoleTextAttribute(hConsole, 15);
	cout << "+-------------< ";
	SetConsoleTextAttribute(hConsole, 12);
	cout << "BOOK OF HEROES";
	SetConsoleTextAttribute(hConsole, 15);
	cout << " >-------------+" << endl;

	vector<pair<string, int>> pairs = s.Read();

	if (!pairs.empty()) {
		sort(pairs.rbegin(), pairs.rend(), sortbysecdesc);

		int i = 0;
		for (auto& v : pairs) {
			SetConsoleTextAttribute(hConsole, i == 0 ? 12 : i >= 1 && i < 3 ? 14 : 10);
			cout << i + 1 << ": " << v.first << " - " << v.second << endl;
			i++;
		}
	}
	else {
		SetConsoleTextAttribute(hConsole, 14);
		cout << "No scoreboard data located! Why not be the first?";
	}

	SetConsoleTextAttribute(hConsole, 12);
	cout << "\n\nPress ENTER to return to main menu\n";
	cin.ignore();
	cin.get();
	main();
}