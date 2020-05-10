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

struct TreeNode{
    int val;
    struct TreeNode * left;
    struct TreeNode * right;
};

typedef struct TreeNode TreeNode;
#define MAX_NODE 1001

TreeNode * dfs(int **tree,int root){
    if(root == -1) return NULL;
    TreeNode * node = (TreeNode *)malloc(sizeof(TreeNode));
    node->val = root;
    node->left = NULL;
    node->right = NULL;

    if(tree[root][0] != -1){
        node->left = dfs(tree,tree[root][0]);
    }
    if(tree[root][1] != -1){
        node->right = dfs(tree,tree[root][1]);
    }
    
    return node;
}

struct TreeNode * BuildTree(int ** relations,int relationSize,int * relationColSize){
    int **tree = (int **)malloc(sizeof(int)*1001);
    int rootIdx = 0;

    for(int i = 0; i <= 1000; ++i){
        tree[i] = (int *)malloc(sizeof(int)*2);
        tree[i][0] = -1;
        tree[i][1] = -1;
    }
    for(int i = 0; i < relationSize; ++i){
        int father = relations[i][1];
        int child = relations[i][0];
        if(father == -1){
            rootIdx = child;
        }else{
            if(tree[father][0] == -1){
                tree[father][0] = child;
            }else{
                tree[father][1] = child;
            }
        }
    }

    return dfs(tree,rootIdx);
}

int main(){
    return 0;
}