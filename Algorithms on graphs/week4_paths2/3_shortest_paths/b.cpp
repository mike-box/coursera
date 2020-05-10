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

int *DivThree(int * nums,int numsSize,int * returnSize){
    int * sum = NULL;
    int * ret = NULL;
    
    sum = (int *)malloc(sizeof(int)*(numsSize+1));
    ret = (int *)malloc(sizeof(int)*2);
    sum[0] = 0;
    for(int i = 0; i < numsSize; ++i){
        sum[i+1] = sum[i] + nums[i];
    }
    for(int i = 1; i < numsSize-3; ++i){
        for(int j = i+2; j < numsSize-1; ++j){
            int l1 = sum[i];
            int l2 = sum[j] - sum[i+1];
            int l3 = sum[numsSize] - sum[j+1];
            if(l1 == l2 && l2 == l3){
                ret[0] = i;
                ret[1] = j;
                *returnSize = 2;
                return ret;
            }
        }
    }

    *returnSize = 0;
    return ret;
}

int main(){
    int num1[9] = {1,3,4,2,2,2,1,1,2};
    int num2[6] = {1,1,1,1,1,1};
    int len = 0;
    int * ret = NULL;
    
    ret = DivThree(num1,9,&len);
    for(int i = 0; i < len; ++i){
        printf("%d\n\r",ret[i]);
    }
    ret = DivThree(num2,6,&len);
    for(int i = 0; i < len; ++i){
        printf("%d\n\r",ret[i]);
    }

    return 0;
}