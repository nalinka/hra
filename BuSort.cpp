#include <vector>
#include <cstdio>

using namespace std;

int main {
  int pocet;
  vector<int> list;
  
  scanf("%d", &pocet);
  list.resize(pocet);
  for(int i =0 ; i < pocet; i++){
    scanf("%d",&list[i]);
  } 
  for(int i= 0; i < list.size; i++){
    for(int j = 0; j< list.size; j ++){
      if(list[j] < list[j+1]){
        continue;
      else{
        list.swap(j; j+1);
      }
      }
    }
  }
}
