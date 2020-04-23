#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <unordered_map>

using std::vector;
using namespace std;



/*
vector<int> fast_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
    vector<int> cnt(points.size());
    int n = starts.size();
    int m = points.size();

    sort(starts.begin(),starts.end());
    sort(ends.begin(),ends.end());
    for(int i = 0; i < m; ++i){
        auto it1 = upper_bound(starts.begin(),starts.end(),points[i]);
        auto it2 = lower_bound(ends.begin(),ends.end(),points[i]);
        int x = it1 - starts.begin();
        int y = it2 - ends.begin();
        cnt[i] = x - y;
    }

    return cnt;
}
*/

vector<int> fast_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
    vector<int> cnt(points.size());
    int n = starts.size();
    int m = points.size();

    sort(starts.begin(),starts.end());
    sort(ends.begin(),ends.end());
    for(int i = 0; i < m; ++i){
        auto it1 = upper_bound(starts.begin(),starts.end(),points[i]);
        auto it2 = lower_bound(ends.begin(),ends.end(),points[i]);
        int x = it1 - starts.begin();
        int y = it2 - ends.begin();
        cnt[i] = x - y;
    }

    return cnt;
}

vector<int> naive_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
  vector<int> cnt(points.size());
  for (size_t i = 0; i < points.size(); i++) {
    for (size_t j = 0; j < starts.size(); j++) {
      cnt[i] += starts[j] <= points[i] && points[i] <= ends[j];
    }
  }
  return cnt;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<int> starts(n), ends(n);
  for (size_t i = 0; i < starts.size(); i++) {
    std::cin >> starts[i] >> ends[i];
  }
  vector<int> points(m);
  for (size_t i = 0; i < points.size(); i++) {
    std::cin >> points[i];
  }
  //use fast_count_segments
  vector<int> cnt = fast_count_segments(starts, ends, points);
  for (size_t i = 0; i < cnt.size(); i++) {
    std::cout << cnt[i] << ' ';
  }
}
