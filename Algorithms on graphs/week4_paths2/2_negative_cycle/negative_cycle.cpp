#include <iostream>
#include <vector>
#include <limits.h>

using std::vector;
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

bool relax(Edge & e,vector<int> & dist,vector<int> & parent){
    
    return true;
}

int negative_cycle(vector<vector<int>> &adj, vector<vector<int>> &cost) {
    //write your code here
    int n = adj.size();
    vector<int> dist(n,1e9+7);
    vector<int> parent(n,-1);
    vector<Edge> edges;

    /*check edges*/
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < adj[i].size(); ++j){
            edges.push_back(Edge(i,adj[i][j],cost[i][j]));
        }
    }

    /*bell-man */
    dist[0] = 0;
    for(int i = 0; i < n-1; ++i){
        for(int j = 0; j < edges.size(); ++j){
          int u = edges[j].u;
          int v = edges[j].v;
          int w = edges[j].weight;
          if(dist[u] + w < dist[v]){
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
        //cout<<u<<":"<<v<<" ="<<w<<endl;
        if(dist[u] + w < dist[v]){
            return 1;
        }
    }

    return 0;
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
  std::cout << negative_cycle(adj, cost);
}
