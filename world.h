#ifndef WORLD_H
#define WORLD_H

#include <vector>

#define WORLD_FREE 0
#define WORLD_FULL 1

class World {
 public:
	World(int w, int h);
	int GetHeight() const;
	int GetWidth() const;
	void Print(int sx, int sy);
	void Shift();
	int Get(int x, int y) const ;
	
 private:
	static int srand_initialized_;
	std::vector<std::vector<int> > map_;
	int w_;
	int h_;
	
};

#endif
