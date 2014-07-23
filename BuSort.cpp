#include <vector>
#include <cstdio>

using namespace std;

int BuSort{
  int pocet;
  vector<int> list;
  
  scanf("%d", &pocet);
  list.resize(pocet);
  for(int k; k < pocet; k++){
    scanf("%d",&list[k]);
  } 
  for(int i; i < list.size; i++{
    for(int j; j< list.size; j ++){
      if(list[j] < list[j+1]){
        continue;
      else{
        list.swap(j; j+1);
      }
      }
    }
  }
}
