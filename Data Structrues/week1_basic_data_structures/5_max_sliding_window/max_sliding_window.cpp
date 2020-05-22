#include <iostream>
#include <vector>
#include <set>
#include <queue>

using std::cin;
using std::cout;
using std::vector;
using namespace std;

typedef pair<int,int> pii;

static bool cmp(const pii & a,const pii & b){
    return a.second < b.second;
}

void max_sliding_window_naive(vector<int> const & A, int w) {
    deque<pii> qu;
    for(int i = 0; i < A.size(); ++i){
        if(qu.empty()){
            qu.push_back(make_pair(i,A[i]));
        }else{
            while(!qu.empty() && A[i] >= qu.back().second){
                qu.pop_back();
            }
            qu.push_back(make_pair(i,A[i]));
        }
        if(i >= w - 1){
            cout<<qu.front().second<<" ";
            if(qu.front().first <= i - w + 1){
                qu.pop_front();
            }
        }
    }
}


int main() {
    int n = 0;
    cin >> n;

    vector<int> A(n);
    for (size_t i = 0; i < n; ++i)
        cin >> A.at(i);

    int w = 0;
    cin >> w;

    max_sliding_window_naive(A, w);

    return 0;
}
