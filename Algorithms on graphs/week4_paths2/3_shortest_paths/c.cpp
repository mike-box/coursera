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

typedef struct ListNode{
    int val;
    struct ListNode * next;
}ListNode;

typedef struct Queue{
    int length;
    ListNode * head;
    ListNode * tail;
}Queue;

void initQueue(Queue * qu){
    qu->length = 0;
    qu->head = NULL;
    qu->tail = NULL;
}

int isEmpty(Queue * qu){
    return qu->length == 0;
}

int popQueue(Queue * qu){
    if(qu->length == 0 || !qu->head) return -1;
    ListNode * curr = qu->head;
    qu->head = qu->head->next;
    int ret = curr->val;
    qu->length--;
    free(curr);
    if(qu->head == NULL){
        qu->tail = NULL;
    }
    return ret;
}

int enQueue(Queue * qu,int val){
    if(!qu) return -1;
    ListNode * node = (ListNode *)malloc(sizeof(ListNode));
    node->val = val;
    node->next = NULL;
    if(qu->head == NULL){
        qu->head = node;
        qu->tail = node;
    }else{
        qu->tail->next =  node;
        qu->tail = qu->tail->next;
    }
    qu->length++;
    return val;
}

int RobotTraining(int n,int **block,int blockSize,int * blockColSize){
    Queue * qu = (Queue *)malloc(sizeof(Queue));
    initQueue(qu);
    int **visit = NULL;
    int d[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
    int step = 0;

    /*intial*/
    visit = (int **)malloc(sizeof(int *)*n);
    for(int i = 0; i < n; ++i){
        visit[i] = (int *)malloc(sizeof(int)*n);
        for(int j = 0; j < n; ++j){
            visit[i][j] = 0;
        }
    }

    enQueue(qu,0);
    visit[0][0] = 1;
    while(!isEmpty(qu)){
        int sz = qu->length;
        for(int i = 0; i < sz; ++i){
            int curr = popQueue(qu);
            int x = curr/n;
            int y = curr%n;
            if(x == n-1 && y == n-1) return step + 1;

            for(int j = 0; j < 4; ++j){
                int x1 = x + d[j][0];
                int y1 = y + d[j][1];
                if(x1 < 0 || x1 >= n || y1 < 0 || y1 >= n) continue;
                if(visit[x1][y1] == 1) continue;
                if(step < blockSize && block[step][0] == x1 && block[step][1] == y1){
                    visit[x1][y1] = 1;
                    continue;
                }
                enQueue(qu,x1*n+y1);
                visit[x1][y1] = 1;
            }
        }
        step++;
    }
    for(int i = 0; i < n; ++i){
        free(visit[i]);
    }
    free(visit);
    free(qu);

    return -1;
}

int main(){
    int **block;
    block = (int **)malloc(sizeof(int *)*3);
    for(int i = 0; i < 3; ++i){
        block[i] = (int *)malloc(sizeof(int)*2);
    }
    block[0][0] = 0;
    block[0][1] = 1;
    block[1][0] = 1;
    block[1][1] = 0;
    block[2][0] = 1;
    block[2][1] = 1;
    printf("step = %d\n\r",RobotTraining(3,block,3,NULL));
    printf("step = %d\n\r",RobotTraining(2,block,0,NULL));
}