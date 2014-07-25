#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

vector <int> bubble(vector<int> list);
vector <int> insert(vector<int> list);
vector <int> mergesort(vector<int> list);

int main(){
  int pocet;
  vector<int> list;
  vector<int> zoznam_vrat;
  scanf("%d", &pocet);
  list.resize(pocet);
  for(int i = 0 ; i < pocet; i++) {
    scanf("%d", &list[i]);
  }
  
  zoznam_vrat = mergesort(list);
  //zoznam_vrat = bubble(list);
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

vector <int> merge(vector<int> left, vector<int> right){
  vector <int> zoznam;
  while(right.size() > 0 || left.size() > 0){
    if(left[0] < right[0]){
      zoznam.push_back(left[0]);
      left.erase(left.begin()); 
    }
    else{
      zoznam.push_back(right[0]);
      right.erase(right.begin()); 
    }
  }
}

vector <int> mergesort(vector<int> list) {
  int m = list.size() / 2;
  vector <int> right;
  vector <int> left;
  
  for(int i = 0; i < m; i++){
    right[i] = list[i];
  }
  for(int i = m; i < list.size(); i++){
    left[i] = list[i];
  }
  
  mergesort(right);
  mergesort(left);
  
  return merge(left, right);  
}


