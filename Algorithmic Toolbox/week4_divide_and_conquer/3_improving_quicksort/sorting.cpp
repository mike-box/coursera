#include <iostream>
#include <vector>
#include <cstdlib>

using std::vector;
using std::swap;

int partition2(vector<int> &a, int l, int r) {
  int x = a[l];
  int j = l;
  for (int i = l + 1; i <= r; i++) {
    if (a[i] <= x) {
      j++;
      swap(a[i], a[j]);
    }
  }
  swap(a[l], a[j]);
  return j;
}

vector<int> partition3(vector<int> & a,int l,int r){
    int x = a[l];
    int j = l;
    int k = l+1;
    vector<int> ret;

    for (int i = l + 1; i <= r; i++) {
        if (a[i] < x) {
            swap(a[k],a[i]);
            swap(a[k++],a[j++]);
        }else if(a[i] == x){
            swap(a[k++],a[i]);
        }
    }

    ret.push_back(j);
    ret.push_back(k);
    return ret;
}

void threeway_quick_sort(vector<int> &a, int l, int r){
  if (l >= r) {
    return;
  }

  int k = l + rand() % (r - l + 1);
  swap(a[l], a[k]);
  vector<int> partion = partition3(a, l, r);
  threeway_quick_sort(a, l, partion[0]-1);
  threeway_quick_sort(a, partion[1], r);
}


void randomized_quick_sort(vector<int> &a, int l, int r) {
  if (l >= r) {
    return;
  }

  int k = l + rand() % (r - l + 1);
  swap(a[l], a[k]);
  int m = partition2(a, l, r);

  randomized_quick_sort(a, l, m - 1);
  randomized_quick_sort(a, m + 1, r);
}



int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  threeway_quick_sort(a, 0, a.size() - 1);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cout << a[i] << ' ';
  }
}
