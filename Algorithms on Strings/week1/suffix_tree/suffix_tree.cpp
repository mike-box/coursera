#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::vector;
using namespace std;

typedef pair<int,int> pii;
int const Letters =    5;
int const NA      =   -1;
struct Node{
    int next [Letters];
    int start;
    int length;
    Node (){
        fill (next, next + Letters, NA);
        this->start = NA;
        this->length = 0;
    }

    bool isLeaf(){
        for(int i = 0; i < Letters; ++i){
            if(this->next[i] == NA) return false; 
        }

        return true;
    }
};

int letterToIndex (char letter)
{
	switch (letter)
	{
        case '$': return 0; break;
		case 'A': return 1; break;
		case 'C': return 2; break;
		case 'G': return 3; break;
		case 'T': return 4; break;
		default: assert (false); return -1;
	}
}

typedef vector<Node> trie;
typedef vector<pii> suffixTrie;
  
// Build a suffix tree of the string text and return a vector
// with all of the labels of its edges (the corresponding 
// substrings of the text) in any order.

int lcs(const string & text,int l1,int l2,int length){
    if(l1 < 0 || l2 < 0) return 0;
    for(int i = 0;i < length; ++i){
        if(text[l1+i] != text[l2+i]) return i;
    }

    return length;
}

bool ComputeSuffixTreeEdges(const string& text) {
  int n = text.size();
  vector<pii> result;
  vector<Node> trie;
  Node node;

  // Implement this function yourself
  trie.push_back(node);
  for(int i = n-1; i >= 0; --i){
      int curr = 0;
      for(int j = i; j < n;){
          int idx = letterToIndex(text[j]);
          int next =  trie[curr].next[idx];      
          if(next == NA){
              trie.push_back(node);
              trie[curr].next[idx] = trie.size()-1;
              curr = trie[curr].next[idx];
              trie[curr].start = j;
              trie[curr].length = n-j;
              break;
          }else{
              int length = lcs(text,trie[next].start,j,trie[next].length);
              if(length == trie[next].length){
                  curr = next;
              }else{
                  trie.push_back(node);
                  trie[curr].next[idx] = trie.size()-1;
                  curr = trie[curr].next[idx];
                  trie[curr].start = j;
                  trie[curr].length = length;
                  trie[next].start  += length;
                  trie[next].length -= length;
                  int x = letterToIndex(text[trie[next].start]);
                  trie[curr].next[x] = next;
              }
              j = j + length;
          }          
      }
  } 

  for(int i = 1; i < trie.size(); ++i){
      cout<<text.substr(trie[i].start,trie[i].length)<<endl;
  }

  return true;
}

int main() {
  string text;
  cin >> text;
  ComputeSuffixTreeEdges(text);  
  return 0;
}
