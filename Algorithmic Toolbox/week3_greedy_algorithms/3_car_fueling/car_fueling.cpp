#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::max;

int compute_min_refills(int dist, int tank, vector<int> & stops) {
    int n = stops.size();
    int fill = 0;
    int curr = tank;

    for(int i = 0; i < n; ++i){
        if(curr >= dist) return fill;
        if(stops[i] + tank < stops[i+1] && i < n-1) return -1;
        if(stops[i] <= curr) continue;
        if(stops[i] > curr){
            if(i == 0)  return -1;
            curr = stops[i-1] + tank;
            fill++;
        }
    }
    
    if(curr >= dist) return fill;
    if(stops[n-1] + tank >= dist) return fill+1; 
    return -1;
}


int main() {
    int d = 0;
    cin >> d;
    int m = 0;
    cin >> m;
    int n = 0;
    cin >> n;

    vector<int> stops(n);
    for (size_t i = 0; i < n; ++i)
        cin >> stops.at(i);

    cout << compute_min_refills(d, m, stops) << "\n";

    return 0;
}
