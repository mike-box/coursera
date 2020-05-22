#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using std::cin;
using std::istringstream;
using std::map;
using std::string;
using std::vector;
using namespace std;

string keys = "ACGT$";
// Preprocess the Burrows-Wheeler Transform bwt of some text
// and compute as a result:
//   * starts - for each character C in bwt, starts[C] is the first position 
//       of this character in the sorted array of 
//       all characters of the text.
//   * occ_count_before - for each character C in bwt and each position P in bwt,
//       occ_count_before[C][P] is the number of occurrences of character C in bwt
//       from position 0 to position P inclusive.
void PreprocessBWT(const string& bwt, 
                   map<char, int>& starts, 
                   map<char, vector<int> >& occ_count_before) {
    // Implement this function yourself
    int n = bwt.size();
    vector<int> count(257,0);
    vector<int> occ(n+1,0);
    string text = "";
    
    for(int i = 0; i < keys.size(); ++i){
        occ_count_before[keys[i]] = occ;
    }
    for(int i = 0; i < n; ++i){
        count[bwt[i]+1]++;
        occ_count_before[bwt[i]][i+1]++;
    }
    for(auto c : keys){
        for(int j = 0; j < n; ++j){
            occ_count_before[c][j+1] += occ_count_before[c][j];
        }
    }
    for(int i = 0; i < 256; ++i){
        count[i+1] += count[i];
    }
    for(int i = 0; i < n; ++i){
        if(!starts.count(bwt[i]))  starts[bwt[i]] = count[bwt[i]];
    }

    /*
    for(auto c : keys){
        cout<<c<<":"<<starts[c]<<endl;
        for(int i = 0; i <= n; ++i){
            cout<<occ_count_before[c][i]<<" ";
        }
        cout<<endl;
    }
    */
}

// Compute the number of occurrences of string pattern in the text
// given only Burrows-Wheeler Transform bwt of the text and additional
// information we get from the preprocessing stage - starts and occ_counts_before.
int CountOccurrences(const string& pattern, 
                     const string& bwt, 
                     map<char, int>& starts, 
                     map<char, vector<int> >& occ_count_before) {
  // Implement this function yourself
  int n = bwt.size();
  int m = pattern.size();
  int top = 0;
  int bottom = n-1;
  int curr = m-1;

  while(top <= bottom){
      if(curr < 0) return bottom - top + 1;
      const char c = pattern[curr--];
      top = starts[c] + occ_count_before[c][top];
      bottom = starts[c] + occ_count_before[c][bottom+1] - 1;
  }

  return 0;
}
     

int main() {
  string bwt;
  cin >> bwt;
  int pattern_count;
  cin >> pattern_count;
  // Start of each character in the sorted list of characters of bwt,
  // see the description in the comment about function PreprocessBWT
  map<char, int> starts;
  // Occurrence counts for each character and each position in bwt,
  // see the description in the comment about function PreprocessBWT
  map<char, vector<int> > occ_count_before;
  // Preprocess the BWT once to get starts and occ_count_before.
  // For each pattern, we will then use these precomputed values and
  // spend only O(|pattern|) to find all occurrences of the pattern
  // in the text instead of O(|pattern| + |text|).
  PreprocessBWT(bwt, starts, occ_count_before);
  for (int pi = 0; pi < pattern_count; ++pi) {
    string pattern;
    cin >> pattern;
    int occ_count = CountOccurrences(pattern, bwt, starts, occ_count_before);
    printf("%d ", occ_count);
  }
  printf("\n");
  return 0;
}
