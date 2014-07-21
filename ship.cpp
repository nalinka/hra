#include "ship.h"

int dx[] = { 0,  0,  0};
int dy[] = {-1,  0, +1};

Ship::Ship() {
	x_ = 0;
	y_ = 0;
}

int abs(int a) {
	if (a < 0)
		return -a;
	return a;
}

int Ship::Decide(const World &world) {
	int best_move = 0;
	double best_score = -100000;	
//	set<pair<int, int> > visited;
// visited.add(make_pair(x, y));
// visited.existuje(make_pair(x, y));
	for (int dy1 = -1; dy1 < 2; dy1++) {
		int y1 = GetY() + dy1;
		int x1 = GetX() + 1;
		if (world.Get(x1, y1) == WORLD_FULL)
			continue;
		double score1 = 0;
		score1 += 100;
		score1 -= abs(y1 - world.GetHeight() / 2);
		if (best_score < score1) {
			best_score = score1;
			best_move = dy1;
		}

		for (int dy2 = -1; dy2 < 2; dy2++) {
			int y2 = y1 + dy2;
			int x2 = x1 + 1;
			double score2 = score1;
			if (world.Get(x2, y2) == WORLD_FULL)
				continue;
			score2 += 100;
			score2 -= abs(y2 - world.GetHeight() / 2);
			if (best_score < score2) {
				best_score = score2;
				best_move = dy1;
			}
			for (int dy3 = -1; dy3 < 2; dy3++) {
				int y3 = y2 + dy3;
				int x3 = x2 + 1;
				double score3 = 300;
				if (world.Get(x3, y3) == WORLD_FULL)
					continue;
				score3 += 100;
				score3 -= 0.01 * abs(y1 - world.GetHeight() / 2);
				score3 -= abs(y3 - world.GetHeight() / 2);
				if (best_score < score3) {
					best_score = score3;
					best_move = dy1;
				}
			
			}
		}
	}
	return best_move + 1;
}

void Ship::Move(int way) {
	x_ += dx[way];
	y_ += dy[way];
}


