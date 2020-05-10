#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <queue>

using std::vector;
using namespace std;

struct Node{
  int x;
  int y;
  double d;
  Node(int x,int y,double d){
      this->x = x;
      this->y = y;
      this->d = d;
  }
};

struct cmp{
   bool operator()(const Node & a,const Node & b){
      return a.d > b.d;
   }
};

int find(vector<int> & f,int x){
    while(x != f[x]){
        x = f[x];
    }

    return x;
}

bool uni(vector<int> & f,int x,int y){
    int x1 = find(f,x);
    int y1 = find(f,y);
    if(x1 == y1) return true;
    f[x1] = y1;
    return true;
}


double minimum_distance(vector<int> x, vector<int> y) {
  double result = 0.0;
  int n = x.size();
  vector<bool> visit(n,false);
  vector<int> f(n,0);
  priority_queue<Node,vector<Node>,cmp> pq;
  //write your code here

  auto distance = [&](int p1,int p2){
      return sqrt(pow(x[p1]-x[p2],2) + pow(y[p1]-y[p2],2));
  };

  for(int i = 0; i < n; ++i){
      f[i] = i;
      for(int j = i + 1; j < n; ++j){
          pq.push(Node(i,j,distance(i,j)));
      }
  }

  while(!pq.empty()){
      Node curr = pq.top();
      pq.pop();
      int x = curr.x;
      int y = curr.y;

      if(find(f,x) == find(f,y)) continue;
      uni(f,x,y);
      result += curr.d;
  }

  return result;
} 

int main() {
  size_t n;
  std::cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cout << std::setprecision(10) << minimum_distance(x, y) << std::endl;
}
