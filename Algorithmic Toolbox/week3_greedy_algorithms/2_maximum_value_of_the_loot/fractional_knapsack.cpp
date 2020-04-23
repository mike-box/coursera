#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using namespace std;

static bool cmp(pair<int,int> & a,pair<int,int> & b){
    double pa = (double)(a.second)/a.first;
    double pb = (double)(b.second)/b.first;
    return pa > pb;
}

double get_optimal_value(int capacity, vector<int> weights, vector<int> values) {
  double value = 0.0;
  int n = weights.size();
  
  // write your code here
  vector<pair<int,int>> loots;
  for(int i = 0; i < n; ++i){
      loots.push_back(make_pair(weights[i],values[i]));
  }
  sort(loots.begin(),loots.end(),cmp);
  for(int i = 0; i < n; ++i){
      if(capacity <= 0) break;
      if(capacity >= loots[i].first){
          value += loots[i].second; 
          capacity -= loots[i].first;
      }else{
          value += double(capacity)/loots[i].first*loots[i].second;
          capacity = 0;
      }
  }

  return value;
}

int main() {
  int n;
  int capacity;
  std::cin >> n >> capacity;
  vector<int> values(n);
  vector<int> weights(n);
  for (int i = 0; i < n; i++) {
    std::cin >> values[i] >> weights[i];
  }

  double optimal_value = get_optimal_value(capacity, weights, values);

  std::cout.precision(10);
  std::cout << optimal_value << std::endl;
  return 0;
}
