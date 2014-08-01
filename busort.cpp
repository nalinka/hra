#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

void PrintVector(vector<int> list) {
  printf("[ ");
  for(int i = 0; i < list.size(); i++){
    printf("%d ",list[i]);
  }
  printf("]\n");
}

vector <int> BubbleSort(vector<int> list) {
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

vector <int> InsertSort(vector<int> list) {
  for(int i = 1; i < list.size(); i++) {
    for(int j = i - 1; j >= 0 ; j--) {
      if(list[j] < list[j-1]) {
          swap(list[j], list[j-1]);
       }
     } 
  }
  return list; 
}

vector <int> MergeSort(vector<int> list) {
  if(list.size() <= 1)
    return list;
  
  int m = list.size() / 2;
  vector <int> right;
  vector <int> left;
  
  for(int i = 0; i < m; i++){
    right.push_back(list[i]);
  }
  for(int i = m; i < list.size(); i++){
    left.push_back(list[i]);
  }
  
  right = MergeSort(right);
  left = MergeSort(left);
  
  //kym jedno alebo druhe nieje na konci,
  //pozri sa na prve meisto v oboch poliach a porovnaj ich. 
  //Mensie z nich push back na koniec retu;
  //v poli z ktoreho si ho zobral sa posun na dalsie miesto 
  vector <int> ret;
  int lp = 0;
  int rp = 0;
  while(rp != right.size() && lp != left.size()){
    if(right[rp] > left[lp]){
      ret.push_back(left[lp]);
      lp++;
    } else {
      ret.push_back(right[rp]);
      rp++;
    }
  }
  while(lp != left.size()){
    ret.push_back(left[lp]);
    lp++;
  } 
  while(rp != right.size()){
    ret.push_back(right[rp]);
    rp++;
  }
  return ret;
}

//najdi pivota a daj ho na koniec
//posuvaj pointer zo zaciatku ku stredu kym nenarazis na cislo vecie nez je pointer
//posuvaj pointer z konca...
// vymen tie cisla
//opakuj kym sa dva pointre netretnu
// zvol pivota....
vector <int> QuickSort(vector<int> list) {
  if(list.size() <= 1)
    return list;
  if(list.size() == 2){
    if(list[0] > list[1])
      swap(list[0], list[1]);
    return list;
  }
  swap(list[list.size() / 2], list[list.size() -1]);
  int sp = 0;
  int ep = list.size() - 2;
  while(sp < ep){
    while(list[sp] < list[list.size() -1]){
      sp++;
    }
    while(list[ep] >= list[list.size() -1]){
      ep--;   
    }
    if(sp < ep)
      swap(list[sp], list[ep]);
  }
  vector <int> left;
  vector <int> right;
  
  for(int i = 0; i < sp; i++){
    left.push_back(list[i]);
  }
  for(int i = sp; i < list.size(); i++){
    right.push_back(list[i]);
  }
  right = QuickSort(right);
  left = QuickSort(left);  
  
  for(int i = 0; i < right.size(); i++){
    left.push_back(right[i]);
  }
  return left;
}

class BuHeap{
 public: 
  vector <int> heap;
 private: 
  void Insert(int bu_new){
    heap.push_back(bu_new);
    int position_new = heap.size() - 1;
    while(heap[position_new] < heap[(position_new / 2) - 1 ]){
        swap(heap[position_new], heap[(position_new / 2) -1 ]);
        position_new = (position_new / 2) -1;
    }
  }
  
  int PopMin(){
    swap(heap[0], heap[heap.size() - 1]);
    int position_start = 0;
    while(heap[2 * position_start +1 ] < heap[position_start] || heap[2 * position_start + 2] < heap[position_start]){
      if(position_start >= heap.size())
        break;
      if(heap[2 * position_start +1 ] < heap[2 * position_start + 2 ]){
        swap(heap[position_start], heap[2 * position_start + 1]);
        position_start = 2 * position_start +1;
      } else{
        swap(heap[position_start], heap[2 * position_start + 2]);
        position_start = 2 * position_start + 2;
      }
    }
    int min = heap[heap.size() - 1];
    heap.pop_back();
    return min; 
  }
};

vector <int> HeapSort(vector<int> list) {
  BuHeap heap;
  for(int i =0; i < list.size(); i++){
    BuHeap::heap.Insert(list[i]);
  } 
}

int main(){
  int pocet;
  vector<int> list;
  scanf("%d", &pocet);
  list.resize(pocet);
  for(int i = 0 ; i < pocet; i++) {
    scanf("%d", &list[i]);
  }
  list = QuickSort(list);
  //list = MergeSort(list);
  //list = BubbleSort(list);
  //list = InsertSort(list);
  
  PrintVector(list);
}

