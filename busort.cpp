#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <sys/time.h>
#include <unistd.h>
#include <vector>

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
    for(int j = i; j > 0 ; j--) {
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
  PrintVector(list);
  while(sp < ep){
    while(list[sp] < list[list.size() -1]){
      sp++;
    }
    while(list[ep] >= list[list.size() -1] && ep >= 0){
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
  for(int i = sp; i < list.size() - 1; i++){
    right.push_back(list[i]);
  }
  right = QuickSort(right);
  left = QuickSort(left);  
  
  left.push_back(list[list.size() - 1]);
  for(int i = 0; i < right.size(); i++){
    left.push_back(right[i]);
  }
  return left;
}

class BuHeap{
 private: 
  vector <int> heap;
 public: 
  void Insert(int bu_new){
    heap.push_back(bu_new);
    int position_new = heap.size() - 1;
    while(heap[position_new] < heap[(position_new - 1)/ 2  ]){
        swap(heap[position_new], heap[(position_new - 1) / 2 ]);
        position_new = (position_new -1)/ 2;
    }
  }
  //prvy prvok v poly vymen s poslednym
  //ak ma dve deti: porovnaj ich a ak tom mensie je mensie nez on vymen ich
  //ak ma jedno dieta porovnaj ho s prvok ak je mensie vymen ich
  //ak deti nema skonci
  void PopMin(){
    swap(heap[0], heap[heap.size() -1]);
    int position_start = 0;
    heap.pop_back();
    while(true){
      //ak nema deti
      if(heap.size() <= 2 * position_start + 1){
        break;
      }
      //ak ma jedno deta
      if(heap.size() <= 2 * position_start + 2  ){
        if(heap[2 * position_start + 1 ] < heap[position_start]){
          swap(heap[2 * position_start + 1 ], heap[position_start]);
        }
        break;
      }
      
      if (heap[2 * position_start + 1] > heap[position_start] && 
          heap[2 * position_start + 2] > heap[position_start]) {
        break;
      }
      if(heap[2 * position_start +1 ] < heap[2 * position_start + 2 ]){
        swap(heap[position_start], heap[2 * position_start + 1]);
        position_start = 2 * position_start +1;
      } else{
        swap(heap[position_start], heap[2 * position_start + 2]);
        position_start = 2 * position_start + 2;
      }
    }
  }
  
  bool Empty() {
    return heap.size() == 0;
  }
  
  bool CheckHeap() {
    for(int i = 0; i < heap.size(); i++)
      if (heap[(i - 1) / 2] > heap[i]) {
        fprintf(stderr, "Heap error %d\n", i);
        return false;
      }
    return true;
  }
  
  int Top() {
    if (heap.size() != 0)
      return heap[0];
    fprintf(stderr, "Requesting top of an empty que\n");
    return -1;
  }
  
  void Print() {
    PrintVector(heap);
  }
};

vector <int> HeapSort(vector<int> list) {
  BuHeap heap;
  for(int i =0; i < list.size(); i++){
    heap.Insert(list[i]);
  }
  vector<int> ret;
  for(int i =0; i < list.size(); i++){
    ret.push_back(heap.Top());
    heap.PopMin();
  }
  return ret;
}

class Timer {
  struct timeval start_;
 public:
  void Start() {
    gettimeofday(&start_, NULL);
  }
  double GetMs() {
    struct timeval cur;
    gettimeofday(&cur, NULL);
    return (cur.tv_sec - start_.tv_sec) * 1000 + 
           (cur.tv_usec - start_.tv_usec) / 1000.0;
  }
};

vector<int> StlSort(vector<int> input) {
  sort(input.begin(), input.end());
  return input;
}

void EvaluateSorts() {
  srand(time(NULL));
  Timer timer;
  vector<int> samples;
  vector<vector<double> > times;
  for(double d = 1; d < 30000; d *= sqrt(sqrt(10)))
    samples.push_back(d);
  vector<function<vector<int>(vector<int>)> > sorts;
  // Add sorting algorithms.
  sorts.push_back(InsertSort);
  sorts.push_back(BubbleSort);
  sorts.push_back(HeapSort);
  sorts.push_back(MergeSort);
  sorts.push_back(QuickSort);
  sorts.push_back(StlSort);
  
  // For each sample size.
  for(int i = 0; i < samples.size(); i++) {
    printf("%7d ", samples[i]);
    vector<int> sample;
    // Generate the sample and get correct answer to be able to check.
    for(int j = 0; j < samples[i]; j++)
      sample.push_back(rand() % 1000);
    vector<int> correct = sample;
    sort(correct.begin(), correct.end());

    // Evaluate each sort.
    for(int j = 0; j < sorts.size(); j++) {
      timer.Start();
      printf("Going to run sort %d\n", j);
      vector<int> answer = sorts[j](sample);
      printf("%7.2lf", timer.GetMs());

      if (answer.size() != samples[i]) {
        printf("Size mismatch %d %d on sort %d\n", answer.size(), samples[i], j);
        continue;
      }
      for(int k = 0; k < samples[i]; k++)
        if (answer[k] != correct[k]) {
          printf("Sort %d gave wrong answer\n", j);
          PrintVector(sample);
          PrintVector(answer);
          PrintVector(correct);
          printf("\n\n", j);
          break;
        }
    }
    printf("\n");
  }
}

int main(){
  EvaluateSorts();
  return 0;
  int pocet;
  vector<int> list;
  scanf("%d", &pocet);
  list.resize(pocet);
  for(int i = 0 ; i < pocet; i++) {
    scanf("%d", &list[i]);
  }
  //list = QuickSort(list);
  //list = MergeSort(list);
  //list = BubbleSort(list);
  list = InsertSort(list);
  //list = HeapSort(list);
  
  PrintVector(list);
}

