#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <algorithm>
#include <string>
#include <limits.h>

using std::vector;
using std::string;
using std::max;
using std::min;
using namespace std;

long long eval(long long a, long long b, char op) {
  if (op == '*') {
    return a * b;
  } else if (op == '+') {
    return a + b;
  } else if (op == '-') {
    return a - b;
  } else {
    assert(0);
  }
}

bool isDigit(const char c){
    return c >= '0' && c <= '9';
}

bool isOp(const char c){
    return c == '+'|| c == '-' || c == '*';
}

long long get_maximum_value(const string &exp) {
  //write your code here
  if(exp.size() == 0) return 0;
  
  int n = (exp.size()+1)/2;
  vector<long long> nums;
  vector<char> op;
  vector<vector<long long>> dp1(n,vector<long long>(n,INT_MAX));
  vector<vector<long long>> dp2(n,vector<long long>(n,INT_MIN));
  /*intial*/
  for(int i = 0; i < exp.size(); ++i){
      if(isDigit(exp[i])) nums.push_back(exp[i] - '0');
      if(isOp(exp[i])) op.push_back(exp[i]);
  }

  for(int i = 0; i < n; ++i){
    dp1[i][i] = nums[i];
    dp2[i][i] = nums[i];
  }
  for(int i = 1; i < n; ++i){
      for(int j = 0; j + i < n; ++j){
          for(int k = j+1; k <= j+i; ++k){
              /*min expression*/
              dp1[j][j+i] = min(dp1[j][j+i],eval(dp1[j][k-1],dp2[k][j+i],op[k-1]));
              dp1[j][j+i] = min(dp1[j][j+i],eval(dp2[j][k-1],dp1[k][j+i],op[k-1]));
              dp1[j][j+i] = min(dp1[j][j+i],eval(dp1[j][k-1],dp1[k][j+i],op[k-1]));
              dp1[j][j+i] = min(dp1[j][j+i],eval(dp2[j][k-1],dp2[k][j+i],op[k-1]));

              /*max expression*/
              dp2[j][j+i] = max(dp2[j][j+i],eval(dp1[j][k-1],dp2[k][j+i],op[k-1]));
              dp2[j][j+i] = max(dp2[j][j+i],eval(dp2[j][k-1],dp1[k][j+i],op[k-1]));
              dp2[j][j+i] = max(dp2[j][j+i],eval(dp1[j][k-1],dp1[k][j+i],op[k-1]));
              dp2[j][j+i] = max(dp2[j][j+i],eval(dp2[j][k-1],dp2[k][j+i],op[k-1]));
          }
          //cout<<"j:"<<j<<" j+i:"<<j+i<<" = "<<dp1[j][j+i]<<endl;
          //cout<<"j:"<<j<<" j+i:"<<j+i<<" = "<<dp2[j][j+i]<<endl;
      }
  }

  return dp2[0][n-1];
}

int main() {
  string s;
  std::cin >> s;
  std::cout << get_maximum_value(s) << '\n';
}
