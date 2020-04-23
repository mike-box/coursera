#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using namespace std;

int optimal_weight(int W, const vector<int> &w) {
  //write your code here
    int n = w.size();
    vector<vector<int>> dp(W+1,vector<int>(n+1,0));

    for(int i = 1; i <= W; ++i){
        for(int j = 1; j <= n; ++j){
            if(w[j-1] <= i){
                dp[i][j] = max(dp[i][j],dp[i-w[j-1]][j-1] + w[j-1]);
            }else{
                dp[i][j] = max(dp[i][j],dp[i][j-1]);
            }
        }
    }

    return dp[W][n];
}

int main() {
  int n, W;
  std::cin >> W >> n;
  vector<int> w(n);
  for (int i = 0; i < n; i++) {
    std::cin >> w[i];
  }
  std::cout << optimal_weight(W, w) << '\n';
}
