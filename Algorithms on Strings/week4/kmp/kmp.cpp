#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <cassert>

using std::cin;
using std::string;
using std::vector;
using namespace std;

int const Letters =   4;
int const NA      =   -1;

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

// Find all occurrences of the pattern in the text and return a
// vector with all positions in the text (starting from 0) where 
// the pattern starts in the text.



vector<int> find_pattern(const string& pattern, const string& text) {
  int n = pattern.size();
  int m = text.size();
  string t = pattern + "$" + text;
  vector<int> result;
  vector<int> prefix(m + n + 1,0);
  // Implement this function yourself
  
  int j = 0;
  for(int i = 1; i < t.size(); ++i){
      while(j > 0 && t[j] != t[i]) j = prefix[j-1];
      if(t[i] == t[j]){
          j++;
      }else{
          j = 0;
      }
      prefix[i] = j;
      if(i > n && prefix[i] == n) 
        result.push_back(i-2*n);
  }

  return result;
}

int main() {
  string pattern, text;
  cin >> pattern;
  cin >> text;
  vector<int> result = find_pattern(pattern, text);
  for (int i = 0; i < result.size(); ++i) {
    printf("%d ", result[i]);
  }
  printf("\n");
  return 0;
}
