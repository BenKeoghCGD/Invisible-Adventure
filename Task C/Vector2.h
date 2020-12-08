#pragma once
class Vector2 {
	struct Direction {
		int x = 0;
		int y = 0;
	};

public:
	int x = 0;
	int y = 0;
	Direction UP = { 0, 1 };
	Direction DOWN = { 0, -1 };
	Direction LEFT = { -1, 0 };
	Direction RIGHT = { 1, 0 };
	Direction NONE = { 0, 0 };
};