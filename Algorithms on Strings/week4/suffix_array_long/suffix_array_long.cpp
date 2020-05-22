#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

using std::cin;
using std::cout;
using std::endl;
using std::make_pair;
using std::pair;
using std::string;
using std::vector;


// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.
vector<int> SortCharacters(const string & text){
    int n = text.size();
    vector<int> count(256,0);
    vector<int> order(n,0);

    for(auto c : text){
        count[c]++;
    }    
    for(int i = 1; i < 256; ++i){
        count[i] += count[i-1];
    }
    for(int i = n-1; i >= 0; --i){
        count[text[i]]--;
        order[count[text[i]]] = i;
    }

    return order;
}

vector<int> ComputeCharClasses(const string & text,vector<int> & order){
    int n = text.size();
    vector<int> res(n,0);
    res[order[0]] = 0;

    for(int i = 1; i < n; ++i){
        if(text[order[i]] != text[order[i-1]]){
            res[order[i]] = res[order[i-1]]+1;
        }else{
            res[order[i]] = res[order[i-1]];
        }
    }

    return res;
}

vector<int> SortDoubled(const string & text,int len,vector<int> & order,vector<int> & classfiy){
    int n = text.size();
    vector<int> count(n,0);
    vector<int> newOrder(n,0);

    for(int i = 0; i < n; ++i){
        count[classfiy[i]]++;
    }
    for(int i = 1; i < n; ++i){
        count[i] += count[i-1];
    }
    for(int i = n-1; i >= 0; --i){
        int start = (order[i]-len+n)%n;
        int cl = classfiy[start];
        count[cl]--;
        newOrder[count[cl]] = start;
    }

    return newOrder;
}

vector<int> UpdateClasses(vector<int> & newOrder,vector<int> & classfiy,int len){
    int n = newOrder.size();
    vector<int> newClassfiy(n,0);
    newClassfiy[newOrder[0]] = 0;
    
    for(int i = 1; i < n; ++i){
        int curr = newOrder[i];
        int prev = newOrder[i-1];
        int mid = curr + len;
        int midPrev = (prev + len)%n;

        if(classfiy[curr] != classfiy[prev] || 
           classfiy[mid] != classfiy[midPrev]){
             newClassfiy[curr] = newClassfiy[prev] + 1;
        }else{
             newClassfiy[curr] = newClassfiy[prev];
        }
    }

    return newClassfiy;
}


vector<int> BuildSuffixArray(const string& text) {
  // Implement this function yourself
  vector<int> order = SortCharacters(text);
  vector<int> classfiy = ComputeCharClasses(text,order);
  int l = 1;
  int n = text.size();

  while(l < n){
      for(int i = 0; i < n; ++i){
          cout<<order[i]<<" ";
      }
      cout<<endl;
      for(int i = 0; i < n; ++i){
          cout<<classfiy[i]<<" ";
      }
      cout<<endl;
      order = SortDoubled(text,l,order,classfiy);
      classfiy = UpdateClasses(order,classfiy,l);
      l = l<<1;
  }

  return order;
}

int main() {
  string text;
  cin >> text;
  vector<int> suffix_array = BuildSuffixArray(text);
  for (int i = 0; i < suffix_array.size(); ++i) {
    cout << suffix_array[i] << ' ';
  }
  cout << endl;
  return 0;
}
