#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

int main() {
  int pocet;
  vector<int> list;
  
  scanf("%d", &pocet);
  list.resize(pocet);
  for(int i =0 ; i < pocet; i++){
    scanf("%d",&list[i]);
  } 
  for(int i= 0; i < list.size(); i++){
    for(int j = 0; j< list.size()-1; j ++){
      if(list[j] < list[j+1]){
        continue;
      }
      else{
        swap(list[i], list[i+1]);
      }
      
    }
  }
  for(int i =0 ; i < pocet; i++){
    printf("%d \n",list[i]);
  } 
}
