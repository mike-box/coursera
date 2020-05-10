#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using std::vector;
using std::pair;
using namespace std;

int number_of_components(vector<vector<int> > &adj) {
  int res = 0;
  int n = adj.size();
  queue<int> qu;
  unordered_set<int> visit;

  //write your code here
  for(int i = 0; i < n; ++i){
      if(visit.count(i)) continue;
      qu.push(i);
      visit.insert(i);
      res++;

      while(!qu.empty()){
          int curr = qu.front();
          qu.pop();

          for(auto v : adj[curr]){
              if(visit.count(v)) continue;
              qu.push(v);
              visit.insert(v);
          }
      }
  }

  return res;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << number_of_components(adj);
}
