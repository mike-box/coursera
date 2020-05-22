#include <algorithm>
#include <cstdio>
#include <map>
#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <cassert>
#include <unordered_map> 
#include <stack>

using std::make_pair;
using std::map;
using std::pair;
using std::string;
using std::vector;
using namespace std;

// Data structure to store edges of a suffix tree.
struct Edge {
  // The ending node of this edge.
  int node;
  // Starting position of the substring of the text 
  // corresponding to the label of this edge.
  int start;
  // Position right after the end of the substring of the text 
  // corresponding to the label of this edge.
  int end;

  Edge(int node_, int start_, int end_) : node(node_), start(start_), end(end_) {}
  Edge(const Edge& e) : node(e.node), start(e.start), end(e.end) {}
};

struct SuffixTreeNode{
   SuffixTreeNode * parent;
   map<char,SuffixTreeNode*> child;
   int depth;
   int start;
   int end;
   SuffixTreeNode(){
      this->parent = NULL;
      this->depth = 0;
      this->start = -1;
      this->end = -1;
   }
};

// Build suffix tree of the string text given its suffix array suffix_array
// and LCP array lcp_array. Return the tree as a mapping from a node ID
// to the vector of all outgoing edges of the corresponding node. The edges in the
// vector must be sorted in the ascending order by the first character of the edge label.
// Root must have node ID = 0, and all other node IDs must be different
// nonnegative integers.
//
// For example, if text = "ACACAA$", an edge with label "$" from root to a node with ID 1
// must be represented by Edge(1, 6, 7). This edge must be present in the vector tree[0]
// (corresponding to the root node), and it should be the first edge in the vector 
// (because it has the smallest first character of all edges outgoing from the root).

bool dfs(SuffixTreeNode * root){
    if(!root) return false;
    if(root->child.size() == 0) return false;
    stack<SuffixTreeNode *> s;
    stack<SuffixTreeNode *> child;

    s.push(root);
    while(!s.empty()){
        SuffixTreeNode * curr = s.top();
        s.pop();

        if(curr->parent) cout<<curr->start<<" "<<curr->end+1<<endl;
        for(auto v : curr->child){
            child.push(v.second);
        }
        while(!child.empty()){
            s.push(child.top());
            child.pop();
        }
    }

    return true;
}

SuffixTreeNode * CreateNewLeaf(SuffixTreeNode * node,const string & text,int suffix){
    SuffixTreeNode * leaf = new SuffixTreeNode();
    leaf->parent = node;
    leaf->depth = text.size()-suffix;
    leaf->start = suffix + node->depth;
    leaf->end = text.size()-1;
    node->child[text[leaf->start]] = leaf;
    return leaf;
}

SuffixTreeNode * BreakEdge(SuffixTreeNode * node,const string & text,int start,int offset){
    char startChar = text[start];
    char midChar = text[start + offset];
    SuffixTreeNode * midNode = new SuffixTreeNode();
    midNode->parent = node;
    midNode->depth = node->depth + offset;
    midNode->start = start;
    midNode->end = start + offset - 1;
    midNode->child[midChar] = node->child[startChar];
    node->child[startChar]->parent = midNode;
    node->child[startChar]->start += offset;
    node->child[startChar] = midNode;

    return midNode;
}

bool realseSuffixTree(SuffixTreeNode * root){
    if(!root) return false;
    if(root->child.size() == 0){
        delete root;
        return true;
    }

    for(auto v : root->child){
        realseSuffixTree(v.second);
    }
    delete root;
    return true;
}

bool SuffixTreeFromSuffixArray(
    const vector<int>& suffix_array,
    const vector<int>& lcp_array,
    const string& text) {
  int n = text.size();
  SuffixTreeNode * root = new SuffixTreeNode();
  root->parent = NULL;
  root->depth = 0;
  root->start = 0;
  root->end = 0;
  // Implement this function yourself
  
  int lcpPrev = 0;
  SuffixTreeNode * currNode = root;
  for(int i = 0; i < n; ++i){
      int suffix = suffix_array[i];
      while(currNode->depth > lcpPrev){
          currNode = currNode->parent;
      }

      if(currNode->depth == lcpPrev){
          currNode = CreateNewLeaf(currNode,text,suffix);
      }else{
          int start = suffix_array[i-1] + currNode->depth;
          int offset = lcpPrev - currNode->depth;
          /*break from the edge*/
          SuffixTreeNode * midNode =  BreakEdge(currNode,text,start,offset);
          /*add new leaf node*/
          currNode = CreateNewLeaf(midNode,text,suffix);
      }

      if(i < n-1){
          lcpPrev = lcp_array[i];
      }
  }

  dfs(root);

  return true;
}


int main() {
  char buffer[200001];
  scanf("%s", buffer);
  string text = buffer;
  vector<int> suffix_array(text.length());
  for (int i = 0; i < text.length(); ++i) {
    scanf("%d", &suffix_array[i]);
  }
  vector<int> lcp_array(text.length() - 1);
  for (int i = 0; i + 1 < text.length(); ++i) {
    scanf("%d", &lcp_array[i]);
  }
  // Build the suffix tree and get a mapping from 
  // suffix tree node ID to the list of outgoing Edges.
  cout<<text<<endl;
  SuffixTreeFromSuffixArray(suffix_array, lcp_array, text);
}
