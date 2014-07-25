#ifndef SORTER_H
#define SORTER_H

#define LINUX
//#define WINDOWS
#define USE_ALLEGRO

void InitSorter();
void Draw();
void NewSample(int size);
int Comp(int i, int j);
void Swap(int i, int j);
void Mark(int i, int val);


#endif

