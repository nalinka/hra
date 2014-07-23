#include "ship.h"

#include <cstdio>
#include <cstdlib>
#include "ship_ai.h"

Ship::Ship() {
	x_ = 0;
	y_ = 0;
}

int dx[] = { 0,  0,  0};
int dy[] = {-1,  0, +1};

void Ship::SetAI(ShipAI *ai) {
  ai_.reset(ai);
  ai_->SetShip(this);
}

int Ship::Decide(const World &world) {
  if (!ai_) {
    fprintf(stderr, "%s: %d: ai_ not initialized.\n", __FILE__, __LINE__);
    return SHIP_STAY;
  }
  return ai_->Decide(world);
}

void Ship::Move(int way) {
	x_ += dx[way];
	y_ += dy[way];
}


