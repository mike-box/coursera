#include<iostream>
#include<vector>
#include<set>
#include<unordered_set>
#include<unordered_map>
#include<string>
#include<stack>
#include<algorithm>
#include<cstdio>

using namespace std;

struct TrieNode{
    int depth;
    int code;
    bool isWord = false;
    TrieNode * next[26];
    TrieNode(){
        this->depth = 0;
        this->code = 0;
        this->isWord = false;
        for(int i = 0; i < 26; ++i){
            this->next[i] = NULL;
        }
    };
};

bool insertTrie(TrieNode * root,string str,int code){
    TrieNode * node = root;
    for(auto c : str){
        if(node->next[c-'a'] == NULL) node->next[c-'a'] = new TrieNode();
        node = node->next[c-'a']; 
    }
    node->depth = str.size();
    node->code = code;
    node->isWord = true;
    return true;
}

int longestPrefix(TrieNode * root, string str){
    int d = 0;
    TrieNode * node = root;
    for(auto c : str){
        if(node->next[c-'a'] == NULL) return d;
        node = node->next[c-'a'];
        d++;
    }

    return d;
}


#define L 256


int main(){
    string str = "abracadabrabrabra";
    string key = "a";
    int code = 41;
    TrieNode * root = new TrieNode();
    unordered_map<string,int> dict;

    for(int i = 0; i < 26; ++i){
        insertTrie(root,key,code);
        dict[key] = code++;
        key[0]++;
    }

    while(str.size() > 0){
        int d = longestPrefix(root,str);
        cout<<"prefix:"<<str.substr(0,d)<<endl;
        cout<<dict[str.substr(0,d)]<<endl;
        if(d < str.size() && code < L){
            insertTrie(root,str.substr(0,d+1),code);
            dict[str.substr(0,d+1)] = code++;
        }
            
        str = str.substr(d);
    }

    return 0;
}