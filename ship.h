#ifndef SHIP_H
#define SHIP_H

#include <memory>
#include "world.h"

#define SHIP_UP 0
#define SHIP_STAY 1
#define SHIP_DOWN 2

class ShipAI;

class Ship {
 public:
 	Ship();
 	int Decide(const World &world);
 	void Move(int way);
 	void SetAI(ShipAI *ai);
 	
 	int GetX() {return x_;}
 	int GetY() {return y_;}
 private:
 	std::shared_ptr<ShipAI> ai_;
 	int x_;
 	int y_;
};

#endif
