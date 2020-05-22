#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

bool dfs(int root,const vector<Node>& tree){
    if(tree.size() == 0) return true;
    if(root == -1) return true;
    int left = tree[root].left;
    int right = tree[root].right;

    auto isLeaf = [&](int curr){
        return tree[curr].left == -1 && tree[curr].right == -1;
    };

    if(isLeaf(root)) return true;
    /*check left*/
    if(left != -1 && tree[root].key <= tree[left].key) return false;
    while(left != -1 && !isLeaf(left)){
        left = tree[left].right;
    }
    if(left != -1 && tree[left].key >= tree[root].key){
        return false;
    }

    /*check right*/
    if(right != -1 && tree[root].key > tree[right].key) return false;
    while(right != -1 && !isLeaf(right)){
        right = tree[right].left;
    }
    if(right != -1 && tree[right].key < tree[root].key){
        return false;
    }

    return dfs(tree[root].left,tree)&&dfs(tree[root].right,tree);
}

bool IsBinarySearchTree(const vector<Node>& tree) {
  // Implement correct algorithm here
  return dfs(0,tree);
}

int main() {
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i) {
    int key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  if (IsBinarySearchTree(tree)){
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
