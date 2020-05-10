#include <iostream>
#include <limits>
#include <vector>
#include <queue>
#include <string.h>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;
using namespace std;

int cmp(const void*a,const void*b)
{
    return *(int*)a-*(int*)b;
}

bool check(const int * arr1,const int * arr2){
    int arrA[3];
    int arrB[3];
    memcpy(arrA,arr1,sizeof(arrA));
    memcpy(arrB,arr2,sizeof(arrB));
    qsort(arrA,3,sizeof(int),cmp);
    qsort(arrB,3,sizeof(int),cmp);
    for(int i = 0; i < 3; ++i){
        if(arrA[i] != arrB[i]) return false;
    }

    return true;
}

int minStep(char * target,char * block){
    int n = strlen(block);
    int l = 0;
    int r = n-1;
    int res = 0;
    int swap = 0;

    while(l < r){
        while(l < r && block[l] == target[l]) l++;
        while(l < r && block[r] == target[r]) r--;
        while(l < r && block[r] != target[l]) r--;
    }
    
    return res;
}

int NumOperations(char * target,char * block){
    int n = strlen(target);
    int res = n;
    int countT[3] = {0};
    int countB[3] = {0};

    for(int i = 0; i < n; ++i){
        countT[target[i]-'a']++;
        countB[block[i]-'a']++;
    }

    if(!(check(countT,countB))){
        return -1;
    }
    
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            if(i == j) continue;
            if(countT[i] == countB[j]){

            }
        }
    }

    return res;
}