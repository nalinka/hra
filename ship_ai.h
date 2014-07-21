#ifndef SHIP_AI_H
#define SHIP_AI_H

#include "world.h"

class Ship;

class ShipAI {
  protected:
	Ship *ship_ = nullptr;
  public:
  	void SetShip(Ship *ship) {ship_ = ship;}
	virtual int Decide(const World &world) = 0;
};

class Exhaustive3Step : ShipAI {
	int Decide(const World &world);
};

#endif
