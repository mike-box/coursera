# python3

import sys
import threading

def max_height(root,tree):
    if root == -1:
        return 0
    l = max_height(tree[root][0],tree)
    r = max_height(tree[root][1],tree)

def compute_height(n, parents):
    # Replace this code with a faster implementation
    root = 0
    tree = [[-1,-1] for i in range(n)]
    for i in range(n):
        if parents[i] == -1:
            root = i
        if tree[parents[i]][0] == -1:
            tree[parents[i]][0] = i
        else:
            tree[parents[i]][1] = i



def main():
    n = int(input())
    parents = list(map(int, input().split()))
    print(compute_height(n, parents))


# In Python, the default limit on recursion depth is rather low,
# so raise it here for this problem. Note that to take advantage
# of bigger stack, we have to launch the computation in a new thread.
sys.setrecursionlimit(10**7)  # max depth of recursion
threading.stack_size(2**27)   # new thread will get stack of such size
threading.Thread(target=main).start()
