#include <iostream>
#include <cassert>
using namespace std;

int gcd_fast(int a, int b) {
    if(a < b) return gcd_fast(b,a);
    if(b == 0) return a;
    return gcd_fast(a%b,b);
}

long long lcm_naive(int a, int b) {
  for (long l = 1; l <= (long long) a * b; ++l)
    if (l % a == 0 && l % b == 0)
      return l;

  return (long long) a * b;
}

long long lcm_fast(long long a, long long b) {  
  return (long long) (a * b)/gcd_fast(a,b);
}

void test_solution() {
    assert(lcm_fast(6,8) == 24);
    assert(lcm_fast(761457,614573) == 467970912861);
}

int main() {
  int a, b;
  std::cin >> a >> b;
  test_solution();
  std::cout << lcm_fast(a, b) << std::endl;
  return 0;
}
