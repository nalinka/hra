#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

vector <int> bubble(vector<int> list);
vector <int> insert(vector<int> list);

int main(){
  int pocet;
  vector<int> list;
  vector<int> zoznam_vrat;
  scanf("%d", &pocet);
  list.resize(pocet);
  for(int i = 0 ; i < pocet; i++) {
    scanf("%d", &list[i]);
  }
  
  zoznam_vrat = bubble(list);
  //zoznam_vrat = insert(list);
  
  for(int i = 0 ; i < list.size(); i++) {
    printf("%d \n", zoznam_vrat[i]);
  }
}

vector <int> bubble(vector<int> list) {
  
  for(int i = 0; i < list.size(); i++) {
    int swaped = 0;
    for(int j = 0; j + 1 < list.size() - i; j++) {
      if(list[j] > list[j + 1]) {
        swap(list[j], list[j + 1]);
        swaped = swaped + 1;
      }
    }
    if (swaped == 0)
      break; 
  }
  
  return list; 
}

vector <int> insert(vector<int> list) {
  
  for(int i = 1; i < list.size(); i++) {
    for(int j = i - 1; j >= 0 ; j--) {
      if(list[j] < list[j-1]) {
          swap(list[j], list[j-1]);
       }
     } 
  }
  return list; 
}

