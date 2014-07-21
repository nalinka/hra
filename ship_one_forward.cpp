#include "ship.h"

int dx[] = {0,  0,  0};
int dy[] = {0,  1, -1};

Ship::Ship() {
	x_ = 0;
	y_ = 0;
}


int Ship::Decide(const World &world) {
	int Position = 0;
	if (GetY() > world.GetHeight() /2 )
		Position = -1;
	if (GetY() == world.GetHeight() /2 )
		Position = 0;
	if (GetY() < world.GetHeight() /2 )
		Position = 1;
		
	bool free_up = world.Get(GetX() + 1, GetY() - 1) == WORLD_FREE;
	bool free_mid = world.Get(GetX() + 1, GetY()) == WORLD_FREE;
	bool free_down = world.Get(GetX() + 1, GetY() + 1) == WORLD_FREE;
	
	// If in lower half.
	if (Position == -1){
		if (free_up)
			return SHIP_UP;
		if (free_mid)
			return SHIP_STAY;
		return SHIP_DOWN;
	}

	// If in middle half.
	if (Position == 0){
		if (free_mid)
			return SHIP_STAY;
		if (free_up)
			return SHIP_UP;
		return SHIP_DOWN;
	}

	// If in upper half.
	if (Position == 1){
		if (free_down)
			return SHIP_DOWN;
		if (free_mid)
			return SHIP_STAY;
		return SHIP_UP;
	}
}

void Ship::Move(int way) {
	x_ += dx[way];
	y_ += dy[way];
}


