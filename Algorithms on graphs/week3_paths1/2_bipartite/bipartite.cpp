#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using std::vector;
using std::queue;
using namespace std;

const int WHITE = 0;
const int BLACK = 1;
typedef pair<int,int> pii;

int bipartite(vector<vector<int> > &adj) {
  int n = adj.size();
  vector<int> visit(n,false);
  vector<int> color(n,false);
  queue<pii> qu;

  //write your code here
  qu.push(make_pair(0,WHITE));
  visit[0] = true;
  color[0] = WHITE;
  while(!qu.empty()){
      pii curr = qu.front();
      qu.pop();

      for(auto v : adj[curr.first]){
          if(visit[v]){
              if(color[curr.first] == color[v]) return 0;
              continue;
          }
          qu.push(make_pair(v,!curr.second));
          visit[v] = true;
          color[v] = !curr.second;
      }
  }

  return 1;
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
  std::cout << bipartite(adj);
}
