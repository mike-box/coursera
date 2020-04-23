#include <iostream>

int get_change(int m) {
  //write your code here
  return (m/10) + ((m%10)/5) + ((m%10)%5);
}

int main() {
  int m;
  std::cin >> m;
  std::cout << get_change(m) << '\n';
}
