#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int get_change(int m) {
  //write your code here
    vector<int> dp(m+1,m);
    dp[0] = 0;
    for(int i = 1; i <= m; ++i){
        if(i >= 4) dp[i] = min(dp[i],dp[i-4] + 1);
        if(i >= 3) dp[i] = min(dp[i],dp[i-3] + 1);
        if(i >= 1) dp[i] = min(dp[i],dp[i-1] + 1);
    }

    return dp[m];
}

int main() {
  int m;
  std::cin >> m;
  std::cout << get_change(m) << '\n';
}
