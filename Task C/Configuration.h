#include <string>
using namespace std;

class Configuration {
	char MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT;

	// ENEMY SETTINGS
	int e_Max, e_CellDmg;

	// PLAYER SETTINGS
	int p_Health, p_MoveDmg;

	// GAME SETTINGS
	int g_MovesToGoal;

public:
	enum Settings { MAX_ENEMIES, DAMAGE_CELL, PLAYER_HEALTH, DAMAGE_MOVE, MOVES_TO_GOAL };

	void changeControl(int handle, char key);
	char getControl(int handle);
	int getSetting(Settings setting);
	void setSetting(Settings setting, int value);
	int getSetting(int setting);
	void setSetting(int setting, int value);
	string intToControl(int handle);
};