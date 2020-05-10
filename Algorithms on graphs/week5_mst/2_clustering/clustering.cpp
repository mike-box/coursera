#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <cmath>
#include <queue>
#include <unordered_set>

using std::vector;
using std::pair;
using namespace std;

struct Node{
    double distance;
    int x;
    int y;
    Node(double d,int x,int y){
        this->distance = d;
        this->x = x;
        this->y = y;
    }
};

int find(vector<int> & f,int x){
    while(x!=f[x]) x = f[x];
    return x;
}

bool uni(vector<int> & f,int x,int y){
    int x1 = find(f,x);
    int y1 = find(f,y);
    f[x1] = y1;
    return true;
}

struct cmp{
    bool operator()(const Node & a,const Node & b){
        return a.distance > b.distance;
    }
};

int countCluster(vector<int> & f){
    unordered_set<int> visit;
    for(int i = 0; i < f.size(); ++i){
        visit.insert(find(f,i));
    }

    return (int)visit.size();
}

double clustering(vector<int> x, vector<int> y, int k) {
  double d = 0.0;
  int n = x.size();
  int count = n;
  vector<int> f(n,0);
  priority_queue<Node,vector<Node>,cmp> pq;

  for(int i = 0; i < n; ++i){
      f[i] = i;
      for(int j = i + 1; j < n; ++j){
          double d = sqrt(pow(x[i]-x[j],2) + pow(y[i]-y[j],2));
          pq.push(Node(d,i,j));
      }
  }
  
  while(!pq.empty() && count >= k){
      Node curr = pq.top();
      pq.pop();
      
      int x = curr.x;
      int y = curr.y;
      if(find(f,x) != find(f,y)){
          uni(f,x,y);
          count--;   
      }
      d = max(d,curr.distance);
  }

  //write your code here
  return d;
} 

int main() {
  size_t n;
  int k;
  std::cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cin >> k;
  std::cout << std::setprecision(10) << clustering(x, y, k) << std::endl;
}
