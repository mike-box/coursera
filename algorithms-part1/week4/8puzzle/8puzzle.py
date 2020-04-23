import random
import sys
import time
import pygame
import heapq
import math
from pygame.locals import *
from heapq import *

LIGHT = (100, 100, 100)
DARK = (200, 200, 200)      # 
BLACK = (0, 0, 0)           # 
RED = (200, 30, 30)         #
BGCOLOR = (40, 40, 60)      #
WIDTH = 800
HEIGHT = 600
NUMBER = 3

class Board:
    def __init__(self,titles):
        if titles is None or len(titles) <= 0:
            return False
        self.blocks = []
        self.dimension = len(titles)
        for i in range(self.dimension):
            row = []
            for j in range(self.dimension):
                row.append(titles[i][j])
            self.blocks.append(row)
    
    def toString(self):
        res = ""
        for i in range(len(self.blocks)):
            for j in range(len(self.blocks[i])):
                res += str(self.blocks[i][j])
            res += "\n"
        return res
    
    def isBlank(self,x,y):
        if x < 0 or x >= self.dimension:
            return True
        if y < 0 or y >= self.dimension:
            return True
        return self.blocks[x][y] == 0
    
    def hamming(self):
        count = 0
        for i in range(self.dimension):
            for j in range(self.dimension):
                if self.blocks[i][j] != (i*self.dimension + j + 1) and not self.isBlank(i,j):
                    count += 1
        return count
    
    def manhattan(self):
        count = 0
        for i in range(self.dimension):
            for j in range(self.dimension):
                correctrow = (self.blocks[i][j] - 1)//self.dimension
                correctcol = (self.blocks[i][j] - 1)%self.dimension
                if not self.isBlank(i,j):
                    count += abs(correctrow-i) + abs(correctcol-j)
        return count
    
    def isGoal(self):
        return self.hamming() == 0
    
    def equals(self,other):
        if other is None:
            return False
        if self.dimension != other.dimension:
            return False
        return self.isArrayEqual(self.blocks,other.blocks)

    def isArrayEqual(self,a,b):
        if len(a) != len(b):
            return False
        
        for i in range(len(a)):
            if len(a[i]) != len(b[i]):
                return False
            for j in range(len(a[i])):
                if a[i][j] != b[i][j]:
                    return False
        
        return True
    
    def setBlocks(self,x,y,val):
        self.blocks[x][y] = val
    
    def getBlocks(self,x,y):
        return self.blocks[x][y]
    
    def neighbors(self):
        res = []
        blankRow = 0
        blankCol = 0

        for i in range(self.dimension):
            for j in range(self.dimension):
                if self.isBlank(i,j):
                    blankRow = i
                    blankCol = j
                    break

        d = [-1, 0, 1, 0, -1]
        for i in range(4):
            x = blankRow + d[i]
            y = blankCol + d[i + 1]
            if x < 0 or x >= self.dimension:
                continue
            if y < 0 or y >= self.dimension:
                continue
            self.setBlocks(blankRow, blankCol,self.getBlocks(x,y))
            self.setBlocks(x, y,0)
            res.append(Board(self.blocks))
            self.setBlocks(x, y, self.getBlocks(blankRow,blankCol))
            self.setBlocks(blankRow, blankCol, 0)
        
        return res
    
    def twin(self):
        for i in range(self.dimension):
            for j in range(self.dimension):
                if not self.isBlank(i,j) and not self.isBlank(i,j+1):
                    v1 = self.blocks[i][j]
                    v2 = self.blocks[i][j+1]
                    self.setBlocks(i,j,v2)
                    self.setBlocks(i,j+1,v1)
                    newboard = Board(self.blocks)
                    self.setBlocks(i,j,v1)
                    self.setBlocks(i,j+1,v2)
                    return newboard

        return None

class SearchNode:
    def __init__(self,state,moves,previous):
        self.state = Board(state.blocks)
        self.previous = previous
        self.moves = moves
        self.priority = self.moves + state.manhattan()
    
    def __gt__(self,other):
        return self.priority > other.priority

    def __ge__(self,other):
        return self.priority >= other.priority

    def __le__(self,other):
        return self.priority <= other.priority

    def __lt__(self,other):
        return self.priority < other.priority

class Slover:
    def __init__(self,initial):
        self.canSlove = True
        self.seqlist = []
        primaryQ = []
        twinQ = []

        primaryStart = SearchNode(initial,0,None)
        twinStart = SearchNode(initial.twin(),0,None)
        heappush(primaryQ,primaryStart)
        heappush(twinQ,twinStart)

        while not primaryQ[0].state.isGoal() and not twinQ[0].state.isGoal():
            primaryCurr = heappop(primaryQ)
            self.addNeigborsToQ(primaryCurr,primaryQ)
            twinCurr = heappop(twinQ)
            self.addNeigborsToQ(twinCurr,twinQ)
        
        if twinQ[0].state.isGoal():
            self.canSlove = False
            return

        if primaryQ[0].state.isGoal():
            self.canSlove = True
            node = primaryQ[0]
            while node is not None:
                self.seqlist.append(node.state)
                node = node.previous
    
    def addNeigborsToQ(self,curr,pq):
        prev = None
        if curr.previous is not None:
            prev = curr.previous.state
        for neg in curr.state.neighbors():
            if neg.equals(prev):
                continue
            heappush(pq,SearchNode(neg,curr.moves + 1,curr))

    def isSolvable(self):
        return self.canSlove
    
    def moves(self):
        if not self.isSolvable():
            return -1
        return len(self.seqlist)-1
    
    def solution(self):
        return self.seqlist

initial = [[1,2,0],[4,8,3],[7,6,5]]
if __name__ == '__main__':
    start = Board(initial)
    s = Slover(start)
    for x in s.solution():
        print(x.toString())
    #for i in range(len(seqlist)):
    #    print(seqlist[i].state.blocks)
    
    
        


