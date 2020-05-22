#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::string;
using std::vector;
using namespace std;

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
      order = SortDoubled(text,l,order,classfiy);
      classfiy = UpdateClasses(order,classfiy,l);
      l = l<<1;
  }

  return order;
}


vector<int> FindOccurrences(const string& pattern, const string& text, const vector<int>& suffix_array) {
  int n = text.size();
  int m = pattern.size();
  string key = text + text;
  vector<int> result;
  int l = 0;
  int r = n;
  int start = 0;
  int end = 0;

  // write your code here
  while(l < r){
      int mid = (l+r)>>1;
      if(pattern > key.substr(suffix_array[mid],m)){
          l = mid + 1;
      }else{
          r = mid;
      }
  }

  start = l;
  r = n;
  while(l < r){
      int mid = (l+r)>>1;
      if(pattern <  key.substr(suffix_array[mid],m)){
          r = mid;
      }else{
          l = mid + 1;
      }
  }
  end = r;

  if(start > end) return result;
  for(int i = start; i < end; ++i){
      result.push_back(suffix_array[i]);
  }

  return result;
}

int main() {
  char buffer[100001];
  scanf("%s", buffer);
  string text = buffer;
  text += '$';
  vector<int> suffix_array = BuildSuffixArray(text);

  int pattern_count;
  scanf("%d", &pattern_count);
  vector<bool> occurs(text.length(), false);
  for (int pattern_index = 0; pattern_index < pattern_count; ++pattern_index) {
    scanf("%s", buffer);
    string pattern = buffer;
    vector<int> occurrences = FindOccurrences(pattern, text, suffix_array);
    for (int j = 0; j < occurrences.size(); ++j) {
      occurs[occurrences[j]] = true;
    }
  }
  for (int i = 0; i < occurs.size(); ++i) {
    if (occurs[i]) {
      printf("%d ", i);
    }
  }
  printf("\n");
  return 0;
}
