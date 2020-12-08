#include "Configuration.h"
#include <string>
#include <iostream>
using namespace std;

void Configuration::changeControl(int handle, char key) { // 0 = up, 1 = down, 2 = left, 3 = right
	switch (handle) {
	case 0:
		MOVE_UP = key;
		break;

	case 1:
		MOVE_DOWN = key;
		break;

	case 2:
		MOVE_LEFT = key;
		break;

	case 3:
		MOVE_RIGHT = key;
		break;

	default:
		cout << "[ERROR] Incorrect handle (changeControl<handle,key>). Inputted Handle: " << handle;
	}
}

char Configuration::getControl(int handle)
{
	switch (handle) {
	case 0:
		return MOVE_UP;

	case 1:
		return MOVE_DOWN;

	case 2:
		return MOVE_LEFT;

	case 3:
		return MOVE_RIGHT;

	default:
		cout << "[ERROR] Incorrect handle (getControl<handle>). Inputted Handle: " << handle;
		return NULL;
	}
}

int Configuration::getSetting(Settings setting)
{
	switch (setting) {
	case MAX_ENEMIES:
		return e_Max;

	case DAMAGE_CELL:
		return e_CellDmg;

	case PLAYER_HEALTH:
		return p_Health;

	case DAMAGE_MOVE:
		return p_MoveDmg;

	case MOVES_TO_GOAL:
		return g_MovesToGoal;

	default:
		cout << "[ERROR] Incorrect setting (getSetting<setting>). Inputted Handle: " << setting;
		return 0;
	}
}

void Configuration::setSetting(Settings setting, int value)
{
	switch (setting) {
	case MAX_ENEMIES:
		e_Max = value;
		break;

	case DAMAGE_CELL:
		e_CellDmg = value;
		break;

	case PLAYER_HEALTH:
		p_Health = value;
		break;

	case DAMAGE_MOVE:
		p_MoveDmg = value;
		break;

	case MOVES_TO_GOAL:
		g_MovesToGoal = value;
		break;

	default:
		cout << "[ERROR] Incorrect setting (setSetting<setting>). Inputted Handle: " << setting;
	}
}

int Configuration::getSetting(int setting)
{
	switch (setting) {
	case 0:
		return e_Max;

	case 1:
		return e_CellDmg;

	case 2:
		return p_Health;

	case 3:
		return p_MoveDmg;

	case 4:
		return g_MovesToGoal;

	default:
		cout << "[ERROR] Incorrect setting (getSetting<setting>). Inputted Handle: " << setting;
		return 'ERR';
	}
}

void Configuration::setSetting(int setting, int value)
{
	switch (setting) {
	case 0:
		e_Max = value;
		break;

	case 1:
		e_CellDmg = value;
		break;

	case 2:
		p_Health = value;
		break;

	case 3:
		p_MoveDmg = value;
		break;

	case 4:
		g_MovesToGoal = value;
		break;

	default:
		cout << "[ERROR] Incorrect setting (setSetting<setting>). Inputted Handle: " << setting;
	}
}

string Configuration::intToControl(int handle)
{
	switch (handle) {
	case 0:
		return "MOVE UP";

	case 1:
		return "MOVE DOWN";

	case 2:
		return "MOVE LEFT";

	case 3:
		return "MOVE RIGHT";

	default:
		cout << "[ERROR] Incorrect handle (getControl<handle>). Inputted Handle: " << handle;
		return "ERR";
	}
}
