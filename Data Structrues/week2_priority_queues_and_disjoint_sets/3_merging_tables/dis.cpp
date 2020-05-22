#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_set>

using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::vector;
using namespace std;

struct DisjointSetsElement {
	int size, parent, rank;
	DisjointSetsElement(int size = 0, int parent = -1, int rank = 0):
	    size(size), parent(parent), rank(rank) {}
};

struct DisjointSets {
	int size;
	int max_table_size;
	vector <DisjointSetsElement> sets;

	DisjointSets(int size): size(size), max_table_size(0), sets(size) {
		for (int i = 0; i < size; i++)
			sets[i].parent = i;
	}

	int getParent(int table) {
		// find parent and compress path
		while(sets[table].parent != table){
			table = sets[table].parent;
		}

		return table;
	}

	void merge(int x, int y) {
		int x1 = getParent(x);
		int y1 = getParent(y);
		if (x1 != y1) {
			if(sets[x1].rank > sets[y1].rank){
                sets[y1].parent = x1;
            }else{
                sets[x1].parent = y1;
                if(sets[x1].rank == sets[y1].rank){
                    sets[y1].rank = sets[x1].rank + 1;
                }
            }
		}		
	}
};


int main(){
    DisjointSets ds(61);
    unordered_set<int> cnt;
    int res = 0;

    /*
    ds.merge(2,10);
    ds.merge(2, 10);
    ds.merge(7, 5);
    ds.merge(6, 1);
    ds.merge(3, 4);
    ds.merge(5, 11);
    ds.merge(7, 8);
    ds.merge(7, 3);
    ds.merge(12, 2);
    ds.merge(9, 6);
    for(int i = 0; i < 13; ++i){
        cnt.insert(ds.getParent(i));
    }
    for(auto x : cnt){
        cout<<x<<":"<<ds.sets[x].rank<<endl;
        res += ds.sets[x].rank;
    }*/
    for(int i = 1; i <= 30; ++i){
        ds.merge(i,2*i);
    }
    for(int i = 1; i <= 20; ++i){
        ds.merge(i,3*i);
    }
    for(int i = 1; i <= 12; ++i){
        ds.merge(i,5*i);
    }
    for(int i = 1; i <= 60; ++i){
        ds.getParent(i);
        res = max(res,ds.sets[i].rank);
    }
    cout<<res<<endl;
    return 0;
}