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

class Exhaustive3StepAI : public ShipAI {
  bool stay_in_mid_;
 public:
  Exhaustive3StepAI(bool stay_in_mid) : stay_in_mid_(stay_in_mid) {};
	int Decide(const World &world);
};

class OneStepForwardAI : public ShipAI {
 public:
	int Decide(const World &world);
};

class BuAI : public ShipAI {
 public:
	int Decide(const World &world);
};

class DFSAI : public ShipAI {
 public:
	int Decide(const World &world);
};

#endif
