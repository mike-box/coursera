#include <iostream>
#include <limits>
#include <vector>
#include <queue>
#include <unordered_set>
#include <limits.h>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;
using namespace std;

struct Edge{
    int u;
    int v;
    int weight;
    Edge(int u,int v,int weight){
        this->u = u;
        this->v = v;
        this->weight = weight;
    }
};

void shortest_paths(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, vector<long long> &distance, vector<int> &reachable, vector<int> &shortest) {
   //write your code here
    int n = adj.size();
    vector<long long> dist(n,INT_MAX);
    vector<int> parent(n,-1);
    vector<Edge> edges;
    unordered_set<int> visit;
    queue<int> qu;

    /*check edges*/
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < adj[i].size(); ++j){
            edges.push_back(Edge(i,adj[i][j],cost[i][j]));
        }
    }

    /*bell-man */
    dist[s] = 0;
    for(int i = 0; i < n-1; ++i){
        for(int j = 0; j < edges.size(); ++j){
          int u = edges[j].u;
          int v = edges[j].v;
          int w = edges[j].weight;
          if(dist[u] != INT_MAX && dist[u] + w < dist[v]){
              dist[v] = w + dist[u];
              parent[v] = u;
          }
        }
    }

    /*check cycle*/
    for(int i = 0; i < edges.size(); ++i){
      int u = edges[i].u;
      int v = edges[i].v;
      int w = edges[i].weight;
      // get all relaxed node
      if(dist[u] != INT_MAX && dist[u] + w < dist[v]){
          visit.insert(v);
      }
    }
    
    for(auto v : visit){
        qu.push(v);
    }
    while(!qu.empty()){
        int curr = qu.front();
        qu.pop();

        for(auto v : adj[curr]){
            if(visit.count(v)) continue;
            qu.push(v);
            visit.insert(v);
        }
    }

    /*check answer*/
    for(int i = 0; i < n; ++i){
        if(dist[i] == INT_MAX){
            reachable[i] = 0;
        }else{
            reachable[i] = 1;
            distance[i] = dist[i];
            if(visit.count(i)) shortest[i] = 0;
        }
    }
}

int main() {
  int n, m, s;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  std::cin >> s;
  s--;
  vector<long long> distance(n, std::numeric_limits<long long>::max());
  vector<int> reachable(n, 0);
  vector<int> shortest(n, 1);
  shortest_paths(adj, cost, s, distance, reachable, shortest);
  for (int i = 0; i < n; i++) {
    if (!reachable[i]) {
      std::cout << "*\n";
    } else if (!shortest[i]) {
      std::cout << "-\n";
    } else {
      std::cout << distance[i] << "\n";
    }
  }
}
