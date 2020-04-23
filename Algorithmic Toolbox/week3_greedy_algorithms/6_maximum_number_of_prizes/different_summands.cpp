#include <iostream>
#include <vector>

using std::vector;

vector<int> optimal_summands(int n) {
  vector<int> summands;
  int m = 0;

  for(int i = 1; i <= n; ++i){
      int rest = n - (i*(i+1)/2);
      if(rest <= i){
          for(int j = 1; j < i; ++j){
              summands.push_back(j);
          }
          summands.push_back(n-(i-1)*i/2);
          break;
      }
  }

  return summands;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> summands = optimal_summands(n);
  std::cout << summands.size() << '\n';
  for (size_t i = 0; i < summands.size(); ++i) {
    std::cout << summands[i] << ' ';
  }
}
