#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using namespace std;

string InverseBWT(const string& bwt) {
  int n = bwt.size();
  int row = 0;
  vector<int> count(257,0);
  vector<int> next(n,0);
  string text = "";
  
  for(int i = 0; i < n; ++i){
      count[bwt[i]+1]++;
      if(bwt[i] == '$') row = i;
  }
  for(int i = 0; i < 256; ++i){
      count[i+1] += count[i];
  }
  for(int i = 0; i < n; ++i){
      next[count[bwt[i]]++] = i; 
  }
  for(int i = 0; i < n; ++i){
      text.push_back(bwt[next[row]]);
      row = next[row];
  }
  // write your code here
  return text;
}

int main() {
  string bwt;
  cin >> bwt;
  cout << InverseBWT(bwt) << endl;
  return 0;
}
