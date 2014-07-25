#include "sorter.h"
/*
InitSorter();
void NewSample(int size);
int Comp(int i, int j);
void Swap(int i, int j);
*/
int main(){
	InitSorter();
	int n = 15;
	NewSample(n);
	
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - 1; j++)
			if (Comp(j, j+1) == -1)
				Swap(j, j+1);
	}
	
}
