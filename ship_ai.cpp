#include "ship_ai.h"

#include "ship.h"

#include <utility>
#include <stack>
#include <vector>
#include <cstdio>

using namespace std;

int abs(int a) {
	if (a < 0)
		return -a;
	return a;
}

int Exhaustive3StepAI::Decide(const World &world) {
	int best_move = 0;
	double best_score = -100000;	
//	set<pair<int, int> > visited;
// visited.add(make_pair(x, y));
// visited.existuje(make_pair(x, y));
	for (int dy1 = -1; dy1 < 2; dy1++) {
		int y1 = ship_->GetY() + dy1;
		int x1 = ship_->GetX() + 1;
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
				if (stay_in_mid_)
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

int OneStepForwardAI::Decide(const World &world) {
 	int Position = 0;
	if (ship_->GetY() > world.GetHeight() /2 )
		Position = -1;
	if (ship_->GetY() == world.GetHeight() /2 )
		Position = 0;
	if (ship_->GetY() < world.GetHeight() /2 )
		Position = 1;
		
	bool free_up = world.Get(ship_->GetX() + 1, ship_->GetY() - 1) == WORLD_FREE;
	bool free_mid = world.Get(ship_->GetX() + 1, ship_->GetY()) == WORLD_FREE;
	bool free_down = world.Get(ship_->GetX() + 1, ship_->GetY() + 1) == WORLD_FREE;
	
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

int BuAI::Decide(const World &world) {
  if (world.Get(ship_->GetX()+1, ship_->GetY()) == WORLD_FULL){
		if(world.Get(1, ship_->GetY() + 1) == WORLD_FULL )		
			return SHIP_UP;
		if(world.Get(1, ship_->GetY() - 1) == WORLD_FULL)		
			return SHIP_DOWN;
		if(world.Get(1, ship_->GetY() - 1) == WORLD_FREE && world.Get(1, ship_->GetY() + 1) == WORLD_FREE)
			if(ship_->GetY() <= world.GetHeight() /2 )			
				return SHIP_DOWN;
			if(ship_->GetY() > world.GetHeight() /2 )			
				return SHIP_UP;
	}
	else{
		if(world.Get(ship_->GetX()+1, ship_->GetY() - 1) == WORLD_FREE || world.Get(ship_->GetX()+1, ship_->GetY() + 1) == 	WORLD_FREE){
			if(ship_->GetY() < world.GetHeight() /2 )			
				return SHIP_DOWN;
			if(ship_->GetY() > world.GetHeight() /2 )			
				return SHIP_UP;
		}
		else
			return SHIP_STAY;
	}
}

int DFSAI::Decide(const World &world) {
  pair<int, int> start = make_pair(ship_->GetX(), ship_->GetY());
  vector< vector <int>> back;
  const int NOT_VISITED = 8;
  back.resize(world.GetWidth());
  for (int i = 0; i < back.size(); i++) {
    back[i].resize(world.GetHeight());
    for (int j = 0; j < back[i].size(); j++) {
      back[i][j] = NOT_VISITED;
    }
  }
  
  int furtherest_dist = 0;
  pair<int, int> furtherest;
  
  stack<pair<int, int>> to_visit;
  to_visit.push(start);
  while (!to_visit.empty()) {
    int x = to_visit.top().first;
    int y = to_visit.top().second;
    to_visit.pop();
    
    if (furtherest_dist < x) {
      furtherest_dist = x;
      furtherest = make_pair(x, y);
    }
    
    for (int i = 0; i < 3; i++) {
      int nx = x + dx[i] + 1;
      int ny = y + dy[i];
      if (world.Get(nx, ny) != WORLD_FREE)
        continue;
      if (back[nx][ny] != NOT_VISITED)
        continue;
      back[nx][ny] = i;
      to_visit.push(make_pair(nx, ny));
    }
    for (int i = 0; i < back[0].size(); i++) {
		  for (int j = 0; j < back.size(); j++) {
				printf("%3d", back[j][i]);
			}
  		printf("\n");
    }	
 		printf("\n");
    
    stack<pair<int, int>> to_visit_copy;
    to_visit_copy = to_visit;
    printf("To visit:");
    while (!to_visit_copy.empty()) {
      printf("(%d %d) ", to_visit_copy.top().first, to_visit_copy.top().second);
      to_visit_copy.pop();
    }
    printf("\n");
    getchar();
  }
  return SHIP_STAY;
}
