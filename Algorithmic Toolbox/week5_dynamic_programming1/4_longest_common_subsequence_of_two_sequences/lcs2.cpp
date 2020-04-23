#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using namespace std;

int lcs2(vector<int> &a, vector<int> &b) {
    int m = a.size();
    int n = b.size();
    vector<vector<int>> dp(m+1,vector<int>(n+1,0));

    for(int i = 1;i <= m; ++i){
        for(int j = 1; j <= n; ++j){
            if(a[i-1] == b[j-1]){
                dp[i][j] = dp[i-1][j-1] + 1;
            }else{
                dp[i][j] = max(dp[i][j],dp[i][j-1]);
                dp[i][j] = max(dp[i][j],dp[i-1][j]);
            }
        }
    }

    return dp[m][n];
}

int main() {
  size_t n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  size_t m;
  std::cin >> m;
  vector<int> b(m);
  for (size_t i = 0; i < m; i++) {
    std::cin >> b[i];
  }

  std::cout << lcs2(a, b) << std::endl;
}
