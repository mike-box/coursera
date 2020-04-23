#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using namespace std;

int edit_distance(const string &str1, const string &str2) {
  int m = str1.size();
  int n = str2.size();
  vector<vector<int>> dp(m+1,vector<int>(n+1,m+n));

  for(int i = 0; i <= m; ++i) dp[i][0] = i;
  for(int i = 0; i <= n; ++i) dp[0][i] = i;
  for(int i = 1; i <= m; ++i){
      for(int j = 1; j <= n; ++j){
          if(str1[i-1] == str2[j-1]){
              dp[i][j] = dp[i-1][j-1];
          }else{
              dp[i][j] = min(dp[i][j],dp[i-1][j] + 1);
              dp[i][j] = min(dp[i][j],dp[i][j-1] + 1);
              dp[i][j] = min(dp[i][j],dp[i-1][j-1] + 1);
          }
      }
  }

  return dp[m][n];
}

int main() {
  string str1;
  string str2;
  std::cin >> str1 >> str2;
  std::cout << edit_distance(str1, str2) << std::endl;
  return 0;
}
