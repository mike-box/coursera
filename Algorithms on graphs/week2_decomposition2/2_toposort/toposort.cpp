#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using std::vector;
using std::pair;
using namespace std;

void dfs(vector<vector<int> > &adj, vector<int> &used, vector<int> &order, int x) {
  //write your code here
}     

vector<int> toposort(vector<vector<int> > adj) {
  int n = adj.size();
  vector<int> used(adj.size(), 0);
  vector<int> order;
  vector<int> indegree(adj.size(),0);
  queue<int> qu;
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
      order.push_back(curr);
      qu.pop();

      for(auto v : adj[curr]){
          indegree[v]--;
          if(indegree[v] == 0){
              qu.push(v);
          }
      }
  }

  return order;
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
  vector<int> order = toposort(adj);
  for (size_t i = 0; i < order.size(); i++) {
    std::cout << order[i] + 1 << " ";
  }
}
