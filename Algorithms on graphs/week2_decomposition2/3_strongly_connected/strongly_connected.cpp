#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>

using std::vector;
using std::pair;
using namespace std;

bool dfs1(vector<vector<int>> & adj,int curr,stack<int> & s,vector<bool> & visit){
    for(auto v : adj[curr]){
        if(visit[v]) continue;
        visit[v] = true;
        dfs1(adj,v,s,visit);
    }
    s.push(curr);

    return true;
}

bool dfs2(vector<vector<int>> & adj,int curr,vector<bool> & visit){
    for(auto v : adj[curr]){
        if(visit[v]) continue;
        visit[v] = true;
        dfs2(adj,v,visit);
    }
    return true;
}

int number_of_strongly_connected_components(vector<vector<int>> & adj) {
    int result = 0;
    int n = adj.size();
    stack<int> post;
    vector<vector<int>> reverseAdj(n,vector<int>());
    vector<bool> visit1(n,false);
    vector<bool> visit2(n,false);

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < adj[i].size(); ++j){
            reverseAdj[adj[i][j]].push_back(i);
        }
    }

    //write your code here
    for(int i = 0; i < n; ++i){
        if(visit1[i]) continue;
        visit1[i] = true;
        dfs1(adj,i,post,visit1);
    }
    while(!post.empty()){
        int curr = post.top();
        post.pop();
        if(visit2[curr]) continue;
        visit2[curr] = true;
        result++;
        dfs2(reverseAdj,curr,visit2);
    }

    return result;
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
  std::cout << number_of_strongly_connected_components(adj);
}
