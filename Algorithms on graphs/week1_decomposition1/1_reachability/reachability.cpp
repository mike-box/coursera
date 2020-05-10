#include <iostream>
#include <vector>
#include<unordered_set>
#include <queue>

using std::vector;
using std::pair;
using namespace std;

int reach(vector<vector<int>> &adj, int x, int y) {
  //write your code here
  unordered_set<int> visit;
  queue<int> qu;

  visit.insert(x);
  qu.push(x);
  while(!qu.empty()){
      int curr = qu.front();
      qu.pop();
      if(curr == y) return 1;

      for(auto v : adj[curr]){
          if(visit.count(v)) continue;
          qu.push(v);
          visit.insert(v);
      }
  }
  
  return 0;
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
  int x, y;
  std::cin >> x >> y;
  std::cout << reach(adj, x - 1, y - 1);
}
