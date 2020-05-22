#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

int const Letters =    6;
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
};

typedef pair<int,int> pii;

int letterToIndex (char letter)
{
	switch (letter)
	{
		case 'A': return 0; break;
		case 'C': return 1; break;
		case 'G': return 2; break;
		case 'T': return 3; break;
		case '#': return 4; break;
		case '$': return 5; break;
		default: assert (false); return -1;
	}
}
  
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

string dfs(vector<Node> & trie,int curr,int length,string & text){
	string res;
	string diff = text;

	if(curr == NA) return text;
	if(trie[curr].start != NA && trie[curr].start < length){
		res.push_back(text[trie[curr].start]);
		return res;
	}

	if(trie[curr].start != NA){
		res = text.substr(trie[curr].start,trie[curr].length);
	}
	for(int i = 0; i < 4; ++i){
		string next = dfs(trie,trie[curr].next[i],length,text);
		if(next.size() < diff.size()){
			diff = next;
		}
	}
	return res + diff;
}


string solve (string p, string q)
{
	string result = p;
	string text = p + "#" +  q  + "$";
	int n = text.size();
	int m = p.size();
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
					trie[curr].start = trie[next].start;
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

	return dfs(trie,0,m,text);
}

int main (void)
{
	string p;
	cin >> p;
	string q;
	cin >> q;

	string ans = solve (p, q);
	cout << ans << endl;

	return 0;
}
