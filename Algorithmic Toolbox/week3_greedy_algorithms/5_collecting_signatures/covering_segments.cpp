#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>

using std::vector;
using namespace std;

struct Segment {
  int start, end;
};

static bool cmp(Segment & a,Segment & b){
    if(a.start == b.start) return a.end < b.end;
    return a.start < b.start;
}

vector<int> optimal_points(vector<Segment> &segments) {
    vector<int> points;

    sort(segments.begin(),segments.end(),cmp);
    int r = segments[0].end;
    for(int i = 1; i < segments.size(); ++i){
        if(segments[i].end <= r){
            r = segments[i].end;
        }else if(segments[i].start > r){
            points.push_back(r);
            r = segments[i].end;
        }
    }
    points.push_back(r);
    return points;
}

int main() {
  int n;
  std::cin >> n;
  vector<Segment> segments(n);
  for (size_t i = 0; i < segments.size(); ++i) {
    std::cin >> segments[i].start >> segments[i].end;
  }
  vector<int> points = optimal_points(segments);
  std::cout << points.size() << "\n";
  for (size_t i = 0; i < points.size(); ++i) {
    std::cout << points[i] << " ";
  }
}
