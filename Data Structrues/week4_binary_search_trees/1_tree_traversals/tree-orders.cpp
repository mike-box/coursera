#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using std::vector;
using std::ios_base;
using std::cin;
using std::cout;
using namespace std;


class TreeOrders {
  int n;
  int root;
  vector <int> key;
  vector <int> left;
  vector <int> right;
public:
  void read() {
    cin >> n;
    key.resize(n);
    left.resize(n);
    right.resize(n);
    for (int i = 0; i < n; i++) {
      cin >> key[i] >> left[i] >> right[i];
    }
  }

  bool dfs1(int root,vector<int> & res){
      if(root == -1) return false; 
      dfs1(left[root],res);
      res.push_back(key[root]);
      dfs1(right[root],res);

      return true;
  }

  vector <int> in_order() {
    vector<int> result;
    // Finish the implementation
    // You may need to add a new recursive method to do that
    dfs1(0,result);
    return result;
  }

  bool dfs2(int root,vector<int> & res){
      if(root == -1) return false; 
      res.push_back(key[root]);
      dfs2(left[root],res);
      dfs2(right[root],res);
      return true;
  }

  vector <int> pre_order() {
    vector<int> result;    
    // Finish the implementation
    // You may need to add a new recursive method to do that
    dfs2(0,result);
    return result;
  }

  bool dfs3(int root,vector<int> & res){
      if(root == -1) return false; 
      dfs3(left[root],res);
      dfs3(right[root],res);
      res.push_back(key[root]);
      return true;
  }

  vector <int> post_order() {
    vector<int> result;
    // Finish the implementation
    // You may need to add a new recursive method to do that
    dfs3(0,result);
    return result;
  }
};

void print(vector <int> a) {
  for (size_t i = 0; i < a.size(); i++) {
    if (i > 0) {
      cout << ' ';
    }
    cout << a[i];
  }
  cout << '\n';
}

int main_with_large_stack_space() {
  ios_base::sync_with_stdio(0);
  TreeOrders t;
  t.read();
  print(t.in_order());
  print(t.pre_order());
  print(t.post_order());
  return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }
#endif

  return main_with_large_stack_space();
}

