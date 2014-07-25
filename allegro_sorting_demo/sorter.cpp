#include "sorter.h"
#include <vector>
#include <algorithm>    // std::random_shuffle
#include <cstdio>

#ifdef USE_ALLEGRO
#include <allegro.h>

BITMAP *backbuff;
#endif

std::vector<int> numbers;
std::vector<int> markers;

int comparing_a = -1;
int comparing_b = -1;

#ifdef LINUX
#include <unistd.h>
#endif
#ifdef WINDOWS
#include <windows.h>
#endif

void mySleep(int sleepMs)
{
#ifdef LINUX
    usleep(sleepMs * 1000);   // usleep takes sleep time in us
#endif
#ifdef WINDOWS
    Sleep(sleepMs);
#endif
}

void InitSorter() {
#ifdef USE_ALLEGRO
	allegro_init();
	set_color_depth(16);
	if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1000, 600, 0, 0) < 0){
		allegro_message ("Neviem nastavit grafickj mod:\n%s\n",allegro_error);
		exit(-1);
	}
	install_keyboard();
	install_timer();
	install_mouse();

	backbuff = create_bitmap(screen->w, screen->h);
#endif
}

void Draw() {
#ifdef USE_ALLEGRO
	if(key[KEY_ESC])
		exit(0);
	
	clear_to_color(backbuff, makecol(255,255,255));
	for (int i = 0; i < numbers.size(); i++) {
		int green = markers[i] * 125;
		int color = makecol(0, green, 0);
		if (i == comparing_a || i == comparing_b)
			color = makecol(255, green, 0);
		rectfill(backbuff, i * screen->w / numbers.size(), screen->h - numbers[i] * screen->h / numbers.size(),
											 (i + 1) * screen->w / numbers.size(), screen->h, color);
	}
	
	blit(backbuff, screen, 0,0,0,0, screen->w, screen->h);
#else
	for (int i = 0; 2 * i < numbers.size(); i++) {
		for (int j = 0; j < numbers.size(); j++) {
			if(numbers[j] > numbers.size() - 2 * i - 1)
				printf(":");
			else if (numbers[j] == numbers.size() - 2 * i - 1)
				printf(".");
			else
				printf(" ");
		}
		printf("\n");
	}
	for (int i = 0; i < numbers.size(); i++) {
		if (i == comparing_a || i == comparing_b)
			printf("O");
		else if(markers[i] == 1)
			printf("#");
		else
			printf(" ");
	}
	printf("\n\n\n");
#endif
	mySleep(30);
}

void NewSample(int size) {
	numbers.resize(size);
	markers.resize(size);
	for (int i = 0; i < numbers.size(); i++) {
		numbers[i] = i + 1;
		markers[i] = 0;
	}
	std::random_shuffle(numbers.begin(), numbers.end());
	Draw();
}

int Comp(int i, int j) {
	comparing_a = i;
	comparing_b = j;
	Draw();
	comparing_a = -1;
	comparing_b = -1;

	if (i < 0 || i >= numbers.size() || j < 0 || j >= numbers.size()) {
		fprintf(stderr, "Trying to compare numbers out of bounds %d %d\n", i, j);
		exit(-1);
	}

	if (numbers[i] == numbers[j]) return 0;
	if (numbers[i] < numbers[j]) return 1;
	return -1;
}

void Swap(int i, int j) {
	if (i < 0 || i >= numbers.size() || j < 0 || j >= numbers.size()) {
		fprintf(stderr, "Trying to swap numbers out of bounds %d %d\n", i, j);
		exit(-1);
	}
	std::swap(numbers[i], numbers[j]);
}

void Mark(int i, int val) {
	markers[i] = val;
}

