#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#include <float.h>

using std::vector;
using std::string;
using std::pair;
using std::min;

struct Point{
  int x,y;
  Point(int x,int y){
    this->x = x;
    this->y = y;
  }
};

static bool cmpX(Point & p1,Point & p2){
    return p1.x < p2.x;
}

static bool cmpY(Point & p1,Point & p2){
    return p1.y < p2.y;
}

double helper(vector<Point> & arr, int l,int r){
    if(r - l <= 1) return DBL_MAX;
    if(r - l == 2) return sqrt(pow(arr[l].x-arr[l+1].x,2) + pow(arr[l].y - arr[l+1].y,2));

    sort(arr.begin()+l,arr.begin()+r,cmpX);
    int mid = (l+r)/2;
    double dl = helper(arr,l,mid);
    double dr = helper(arr,mid,r);
    double d = min(dl,dr);
    int ml = l;
    int mr = r-1;
    while(ml < r && abs(arr[ml].x - arr[mid].x) > d) ml++;
    while(mr >= l && abs(arr[mr].x - arr[mid].x) > d) mr--;
    sort(arr.begin() + ml,arr.begin() + mr + 1,cmpY);

    for(int i = l; i <= mr ; ++i){
        for(int j = i + 1; j <= mr && j <= i + 7; ++j){
            double dy = sqrt(pow(arr[i].x-arr[j].x,2) + pow(arr[i].y-arr[j].y,2));
            d = min(d,dy);
        }
    }

    return d;
}

double minimal_distance(vector<int> x, vector<int> y) {
  int n = x.size();
  vector<Point> arr;

  for(int i = 0; i < n ; ++i){
    arr.push_back(Point(x[i],y[i]));
  }

  return helper(arr,0,n);
}

int main() {
  size_t n;
  std::cin >> n;
  vector<int> x(n);
  vector<int> y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cout << std::fixed;
  std::cout << std::setprecision(9) << minimal_distance(x, y) << "\n";
}
