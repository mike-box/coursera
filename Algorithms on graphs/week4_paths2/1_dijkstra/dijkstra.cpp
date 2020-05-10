#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits.h>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;
using namespace std;

typedef pair<int,int> pii;

int distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t) {
  //write your code her
  int n = adj.size();
  vector<int> dist(n,INT_MAX);
  queue<pii> qu;

  dist[s] = 0;
  qu.push(make_pair(s,0));
  while(!qu.empty()){
      pii curr = qu.front();
      qu.pop();

      for(int i = 0; i < adj[curr.first].size(); ++i){
          int v = adj[curr.first][i];
          int w = cost[curr.first][i];
          if((curr.second + w) < dist[v]){
              dist[v] = curr.second + w;
              qu.push(make_pair(v,dist[v]));
          }
      }
  }

  if(dist[t] == INT_MAX) return -1;
  return dist[t];
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, cost, s, t);
}
