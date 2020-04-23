#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <stdlib.h>

using std::vector;
using namespace std;

int dp[21][201][201];

int partition3(vector<int> &A) {
    int all = 0;
    int div = 0;
    int n = A.size();

    memset(dp,0,sizeof(dp));
    for(int i = 0; i < A.size(); ++i){
        all += A[i];
    }
    if(all%3 != 0) return 0;
    div = all/3;

    /*intiail*/
    dp[0][0][0] = 1;
    for(int i = 1; i <= n; ++i){
        for(int j = 0; j <= div; ++j){
            for(int k = 0; k <= div; ++k){
                dp[i][j][k] = dp[i][j][k]||dp[i-1][j][k];
                if(j >= A[i-1]) dp[i][j][k] = dp[i][j][k]||dp[i-1][j-A[i-1]][k];
                if(k >= A[i-1]) dp[i][j][k] = dp[i][j][k]||dp[i-1][j][k-A[i-1]];
            }
        }
    }

    return dp[n][div][div];
}

int main() {
  int n;
  std::cin >> n;
  vector<int> A(n);
  for (size_t i = 0; i < A.size(); ++i) {
    std::cin >> A[i];
  }
  std::cout << partition3(A) << '\n';
}
