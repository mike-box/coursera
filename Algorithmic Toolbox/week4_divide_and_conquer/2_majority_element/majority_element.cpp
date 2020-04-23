#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;
using namespace std;

int get_majority_element(vector<int> &a, int left, int right) {
    sort(a.begin(),a.end());
    
    int curr = a[0];
    int cnt = 0;
    int n = a.size();
    for(int i = 0; i < n; ++i){
        if(a[i] == curr){
            cnt++;
        }else{
            if(cnt > (n/2)) return 1;
            curr = a[i];
            cnt = 1;
        }
    }

    if(cnt > (n/2)) return 1;
    return -1;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  std::cout << (get_majority_element(a, 0, a.size()) != -1) << '\n';
}
