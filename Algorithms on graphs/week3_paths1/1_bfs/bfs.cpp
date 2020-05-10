#include <iostream>
#include <vector>
#include <queue>
#include <queue>


using std::vector;
using std::queue;
using namespace std;

int distance(vector<vector<int> > &adj, int s, int t) {
  int n = adj.size();
  int step = 0;
  vector<int> visit(n,false);
  queue<int> qu;
  //write your code here

  qu.push(s);
  visit[s] = true;
  while(!qu.empty()){
      int sz = qu.size();
      for(int i = 0; i < sz; ++i){
          int curr = qu.front();
          qu.pop();
          if(curr == t) return step;

          for(auto v : adj[curr]){
              if(visit[v]) continue;
              qu.push(v);
              visit[v] = true;
          }
      }
      step++;
  }

  return -1;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, s, t);
}
