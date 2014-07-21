#include "ship.h"

int dx[] = {0,  0,  0};
int dy[] = {0,  1, -1};

Ship::Ship() {
	x_ = 0;
	y_ = 0;
}

int Ship::Decide(const World &world) {
	if (world.Get(GetX()+1, GetY()) == WORLD_FULL){
		if(world.Get(1, GetY() + 1) == WORLD_FULL )		
			return SHIP_UP;
		if(world.Get(1, GetY() - 1) == WORLD_FULL)		
			return SHIP_DOWN;
		if(world.Get(1, GetY() - 1) == WORLD_FREE && world.Get(1, GetY() + 1) == WORLD_FREE)
			if(GetY() <= world.GetHight() /2 )			
				return SHIP_DOWN;
			if(GetY() > world.GetHight() /2 )			
				return SHIP_UP;
	}
	else{
		if(world.Get(GetX()+1, GetY() - 1) == WORLD_FREE || world.Get(GetX()+1, GetY() + 1) == 	WORLD_FREE){
			if(GetY() < world.GetHight() /2 )			
				return SHIP_DOWN;
			if(GetY() > world.GetHight() /2 )			
				return SHIP_UP;
		}
		else
			return SHIP_STAY;
	}
}

void Ship::Move(int way) {
	x_ += dx[way];
	y_ += dy[way];
}

