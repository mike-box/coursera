#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int const Letters =    4;
int const NA      =   -1;

struct Node
{
	int next [Letters];

	Node ()
	{
		fill (next, next + Letters, NA);
	}

	bool isLeaf () const
	{
	    return (next[0] == NA && next[1] == NA && next[2] == NA && next[3] == NA);
	}
};

int letterToIndex (char letter)
{
	switch (letter)
	{
		case 'A': return 0; break;
		case 'C': return 1; break;
		case 'G': return 2; break;
		case 'T': return 3; break;
		default: assert (false); return -1;
	}
}

vector<Node>  buildTrie(const vector<string> & patterns){
	vector<Node> trie;
	Node node;
	trie.push_back(node);

	for(auto  p : patterns){
		int curr  = 0;
		for(auto c : p){
			int idx = letterToIndex(c);
			if(trie[curr].next[idx] == NA){
				trie.push_back(node);
				trie[curr].next[idx] = trie.size()-1;
			}
			curr = trie[curr].next[idx];
		}
	}

	return trie;
}

bool searchTrie(const vector<Node> & trie,const string & text,int start){
	int curr = 0;
	for(int i = start; i < text.size(); ++i){
		int idx = letterToIndex(text[i]);
		curr = trie[curr].next[idx];
		if(curr == NA) return false;
		if(trie[curr].isLeaf()) return true;
	}

	return false;
}

vector <int> solve (const string& text, int n, const vector <string>& patterns)
{
	vector<int> result;
	vector<Node> trie = buildTrie(patterns);
	// write your code here
	for(int i = 0; i < text.size(); ++i){
		if(searchTrie(trie,text,i)){
			result.push_back(i);
		}
	}

	return result;
}

int main (void)
{
	string t;
	cin >> t;

	int n;
	cin >> n;

	vector <string> patterns (n);
	for (int i = 0; i < n; i++)
	{
		cin >> patterns[i];
	}

	vector <int> ans;
	ans = solve (t, n, patterns);

	for (int i = 0; i < (int) ans.size (); i++)
	{
		cout << ans[i];
		if (i + 1 < (int) ans.size ())
		{
			cout << " ";
		}
		else
		{
			cout << endl;
		}
	}

	return 0;
}
