#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>
#include <unordered_map>

using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::vector;
using namespace std;

typedef pair<int,int> pii;
struct Node{
    unordered_map<char,int> next;
    int start;
};

typedef vector<Node> trie;
typedef vector<pii> suffixTrie;
  
// Build a suffix tree of the string text and return a vector
// with all of the labels of its edges (the corresponding 
// substrings of the text) in any order.

bool dfs(trie & t,int count,int root,suffixTrie & st){
    if(t[root].next.size() == 0 || t[root].next.size() > 1){
        if(count > 0) st.push_back(make_pair(t[root].start-count+1,count));
    }
    
    if(t[root].next.size() > 1) count = 0;
    for(auto v : t[root].next){
        dfs(t,count+1,v.second,st);
    }

    return true;
}

vector<pii> ComputeSuffixTreeEdges(const string& text) {
  int n = text.size();
  vector<pii> result;
  vector<Node> trie;
  Node node;

  // Implement this function yourself
  trie.push_back(node);
  for(int i = n-1; i >= 0; --i){
      int curr = 0;
      for(int j = i; j < n; ++j){
          if(!trie[curr].next.count(text[j])){
              trie.push_back(node);
              trie[curr].next[text[j]] = trie.size()-1;
          }
          curr = trie[curr].next[text[j]];
          trie[curr].start = j;
      }
  }

  dfs(trie,0,0,result);
  return result;
}

int main() {
  string text;
  cin >> text;
  vector<pii> edges = ComputeSuffixTreeEdges(text);
  for (int i = 0; i < edges.size(); ++i) {
      for(int j = 0; j < edges[i].second; ++j){
          cout<<text[edges[i].first+j];
      }
      cout<<endl;
  }

  return 0;
}
