#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;
using namespace std;

long long max_dot_product(vector<int> a, vector<int> b) {
    vector<pair<int,int>> arr;
    long long revenue = 0;
    
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    for(int i = 0; i < a.size(); ++i){
        revenue += (long long)(a[i])*b[i];
    }

    return revenue;
}

int main() {
  size_t n;
  std::cin >> n;
  vector<int> a(n), b(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> a[i];
  }
  for (size_t i = 0; i < n; i++) {
    std::cin >> b[i];
  }
  std::cout << max_dot_product(a, b) << std::endl;
}
