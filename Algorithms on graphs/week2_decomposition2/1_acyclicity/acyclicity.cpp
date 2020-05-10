#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

using std::vector;
using std::pair;
using namespace std;

int acyclic(vector<vector<int> > &adj) {
  int n = adj.size();
  int visit = 0;
  queue<int> qu;
  vector<int> indegree(n,0);

  //write your code here  
  for(int i = 0; i < n; ++i){
      for(int j = 0; j < adj[i].size(); ++j){
          indegree[adj[i][j]]++;
      }
  }
  for(int i = 0; i < n; ++i){
      if(indegree[i] == 0){
          qu.push(i);
      }
  }

  while(!qu.empty()){
      int curr = qu.front();
      visit++;
      qu.pop();

      for(auto v : adj[curr]){
          indegree[v]--;
          if(indegree[v] == 0){
              qu.push(v);
          }
      }
  }

  if(visit == n) return 0;
  return 1;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  std::cout << acyclic(adj);
}
