#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

static bool cmp(string & a,string & b){
    string s1 = a + b;
    string s2 = b + a;
    return s1 > s2;
}

string largest_number(vector<string> a) {
  //write your code here
  std::stringstream ret;
  sort(a.begin(),a.end(),cmp);
  for (size_t i = 0; i < a.size(); i++) {
    ret << a[i];
  }
  string result;
  ret >> result;
  return result;
}

int main() {
  int n;
  std::cin >> n;
  vector<string> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  std::cout << largest_number(a);
}
