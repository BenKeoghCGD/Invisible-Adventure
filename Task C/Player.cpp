#include "Player.h"
using namespace std;

int Player::Health() {
	return health;
}

void Player::Health(int health) {
	Player::health = health;
}