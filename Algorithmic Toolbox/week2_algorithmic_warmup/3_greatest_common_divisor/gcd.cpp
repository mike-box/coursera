#include <iostream>

int gcd_naive(int a, int b) {
    if(a < b) return gcd_naive(b,a);
    if(b == 0) return a;
    return gcd_naive(a%b,b);
}

int main() {
  int a, b;
  std::cin >> a >> b;
  std::cout << gcd_naive(a, b) << std::endl;
  return 0;
}
