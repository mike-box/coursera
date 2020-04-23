#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

vector<int> optimal_sequence(int n) {
  std::vector<int> sequence;
  vector<int> dp(n+1,n);
  vector<int> op(n+1,0);

  dp[1] = 0;
  for(int i = 2; i <= n; ++i){
      dp[i] = dp[i-1] + 1;
      op[i] = 1;
      if(i%3 == 0 && dp[i] > dp[i/3] + 1){
          dp[i] = dp[i/3] + 1;
          op[i] = 3;
      }
      if(i%2 == 0 && dp[i] > dp[i/2] + 1){
          dp[i] = dp[i/2] + 1;
          op[i] = 2;
      }
  }

  sequence.push_back(n);
  while(n != 1){
      if(op[n] == 1) n -= 1;
      else if(op[n] == 2) n /= 2;
      else if(op[n] == 3) n /= 3;
      sequence.push_back(n);
  }
  reverse(sequence.begin(),sequence.end());
  return sequence;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> sequence = optimal_sequence(n);
  std::cout << sequence.size() - 1 << std::endl;
  for (size_t i = 0; i < sequence.size(); ++i) {
    std::cout << sequence[i] << " ";
  }
}
