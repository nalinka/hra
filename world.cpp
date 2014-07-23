#include "world.h"

#include <ctime>
#include <cstdio>
#include <cstdlib>

int World::srand_initialized_ = 0;

World::World(int w, int h) {
	h_ = h;
	w_ = w;
	map_.resize(h);
	for (int i = 0; i < map_.size(); i++) {
		map_[i].resize(w);
		for (int j = 0; j < map_[i].size(); j++)
			map_[i][j] = WORLD_FREE;
	}
	if (srand_initialized_ == 0) {
		srand(time(NULL));
		srand_initialized_++;
	}
}

int World::GetHeight() const {
	return h_;
}

int World::GetWidth() const {
	return w_;
}

int World::Get(int x, int y) const {
	if (x < 0 || x >= w_ || y < 0 || y >= h_)
		return WORLD_FULL;
	return map_[y][x];
}


void World::Print(int sx, int sy) {
	printf("\n\n\n\n");
	for (int i = 0; i < map_.size(); i++) {
		for (int j = 0; j < map_[i].size(); j++) {
			if (j == sx && i == sy) {
				printf("O");
			} else {
				if (map_[i][j] == WORLD_FREE) {
					printf(".");
				}	else {
					printf("#");
				}
			}
		}
		printf("\n");
	}
}

void World::Shift() {
	for (int i = 0; i < map_.size(); i++)
		for (int j = 0; j + 1 < map_[i].size(); j++)
			map_[i][j] = map_[i][j + 1];
	for (int i = 0; i < map_.size(); i++)
		map_[i].back() = (rand() % 100 < 30);
}

