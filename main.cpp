#include <cstdio>
#include <unistd.h>
#include <cmath>

#include "ship.h"
#include "ship_ai.h"
#include "world.h"

int PlayGame(){
	int w = 40;
	int h = 15;
	World world(w, h);
	Ship bu;
  bu.SetAI(new Exhaustive3Step());
	int survive_time = -w;
	bool printing = false;
	while(1) {
		// Get user update
		int bu_way = bu.Decide(world);

		// Do game logic
		world.Shift();
		bu.Move(bu_way);
		if (world.Get(bu.GetX(), bu.GetY()) == WORLD_FULL)
			break;
		survive_time++;
		
		// Show output
		if (printing) {
			world.Print(bu.GetX(), bu.GetY());
			printf("Survive time: %d\n", survive_time);
			usleep(200000);
		}
	}
	
	if (printing)
		printf("\n\nGAME OVER\nYou survived for %d\n", survive_time);
	return survive_time;	
}

int main() {
	int N = 10000;
	double sum = 0;
	double sum2 = 0;
	for( int i = 0; i < N; i++) {
		int survival = PlayGame();
		sum += survival;
		sum2 += survival * survival;
	}
	sum /= N;
	sum2 /= N;
	
	double stdev = sqrt(sum2 - sum * sum);
	double err_mean = stdev / sqrt(N);
	printf("Mean survived time is %.2lf\n", sum);
	printf("Standard diviation is %.2lf\n", stdev);
	printf("Error in mean is %.2lf\n", err_mean);
}
