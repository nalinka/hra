#ifndef SHIP_AI_H
#define SHIP_AI_H

#include "world.h"

class Ship;

class ShipAI {
 protected:
  Ship *ship_;
 public:
  ShipAI() : ship_(nullptr) {};
  void SetShip(Ship *ship) {ship_ = ship;}
  virtual int Decide(const World &world) = 0;
};

class Exhaustive3Step : public ShipAI {
	int Decide(const World &world);
};

#endif
