---
title: 【leetcode】 170周比赛
tags: leetcode
categories: 算法
---

# 170比赛
本周题目比较简单，基本上都是常规题目。

 
## 5303. 解码字母到整数映射
### 题目
给你一个字符串 ```s```，它由数字```（'0' - '9'）```和``` '#' ```组成。我们希望按下述规则将 s 映射为一些小写英文字符：

+ 字符```（'a' - 'i'）```分别用```（'1' - '9'）```表示。
+ 字符```（'j' - 'z'）```分别用```（'10#' - '26#'）```表示。 
返回映射之后形成的新字符串。
题目数据保证映射始终唯一。

示例 1：
```
输入：s = "10#11#12"
输出："jkab"
解释："j" -> "10#" , "k" -> "11#" , "a" -> "1" , "b" -> "2".
```
示例 2：
```
输入：s = "1326#"
输出："acz"
```
示例 3：
```
输入：s = "25#"
输出："y"
```
示例 4：
```
输入：s = "12345678910#11#12#13#14#15#16#17#18#19#20#21#22#23#24#25#26#"
输出："abcdefghijklmnopqrstuvwxyz" 

```
提示：

+ ```1 <= s.length <= 1000```
+ ```s[i]``` 只包含数字```（'0'-'9'）```和 ```'#' ```字符。
+ ```s ```是映射始终存在的有效字符串。

### 地址
https://leetcode-cn.com/problems/decrypt-string-from-alphabet-to-integer-mapping
### 题意
>  直接翻译即可
### 思路
1. 按照题目中规定的替换原则，如果替换时出现了```#```,则前两位的数字一定大于```9```;
2. 我们只需要判断当前的字符串后面紧跟的第三位是否为```#```即可；
### 代码
```c++
class Solution {
public:
    string freqAlphabets(string s) {
        string res;
        int n = s.size();
        
        for(int i = 0; i < s.size();){
            if((i+2) < n && s[i+2] == '#'){
                res.push_back('a' + stoi(s.substr(i,2))-1);
                i += 3;
            }else{
                res.push_back('a' + stoi(s.substr(i,1))-1);
                i += 1;
            }
        }
        
        return res;
    }
};
```

## 5304. 子数组异或查询
### 题目
有一个正整数数组 ```arr```，现给你一个对应的查询数组 ```queries```，其中 ```queries[i] = [Li, Ri]```。

对于每个查询 i，请你计算从``` Li``` 到``` Ri``` 的``` XOR ```值（即 ```arr[Li] xor arr[Li+1] xor ... xor arr[Ri]```）作为本次查询的结果。

并返回一个包含给定查询 ```queries ```所有结果的数组。

 

示例 1：
```
输入：arr = [1,3,4,8], queries = [[0,1],[1,2],[0,3],[3,3]]
输出：[2,7,14,8] 
解释：
数组中元素的二进制表示形式是：
1 = 0001 
3 = 0011 
4 = 0100 
8 = 1000 
查询的 XOR 值为：
[0,1] = 1 xor 3 = 2 
[1,2] = 3 xor 4 = 7 
[0,3] = 1 xor 3 xor 4 xor 8 = 14 
[3,3] = 8
```
示例 2：
```
输入：arr = [4,8,2,10], queries = [[2,3],[1,3],[0,0],[0,3]]
输出：[8,0,4,4] 

```

提示：
+ ```1 <= arr.length <= 3 * 10^4```
+ ```1 <= arr[i] <= 10^9```
+ ```1 <= queries.length <= 3 * 10^4```
+ ```queries[i].length == 2```
+ ```0 <= queries[i][0] <= queries[i][1] < arr.length```

### 地址
https://leetcode-cn.com/problems/xor-queries-of-a-subarray
### 题意
>  利用异或的特性即可
### 思路
1. 利用异或的特性，```x^x = 0```,```x^0 = x```,只要知道异或的基本性质，本题非常简单;
2. 利用前```n```项的异或即可，```xor[i][j] = xor[j]^xor[i-1]```;
### 代码
```c++
class Solution {
public:
    vector<int> xorQueries(vector<int>& arr, vector<vector<int>>& queries) {
        int n = arr.size();
        vector<int> xo(n+1,0);
        vector<int> res;
        
        for(int i = 0; i < n; ++i){
            xo[i+1] = xo[i]^arr[i];
        }
        for(auto & query: queries){
            res.push_back(xo[query[0]]^xo[query[1]+1]);
        }
        
        return res;
    }
};
```

## 5305. 获取你好友已观看的视频
### 题目
有``` n ```个人，每个人都有一个 ``` 0 ```到 ```n-1 ```的唯一``` id``` 。

给你数组 ```watchedVideos ``` 和 ```friends ```，其中 ```watchedVideos[i] ``` 和 ```friends[i] ```分别表示 ```id = i``` 的人观看过的视频列表和他的好友列表。

```Level 1 ```的视频包含所有你好友观看过的视频，```level 2 ```的视频包含所有你好友的好友观看过的视频，以此类推。一般的，```Level``` 为 ```k``` 的视频包含所有从你出发，最短距离为 k 的好友观看过的视频。

给定你的 ```id ``` 和一个 level 值，请你找出所有指定 level 的视频，并将它们按观看频率升序返回。如果有频率相同的视频，请将它们按名字字典序从小到大排列。

 

示例 1：
```
输入：watchedVideos = [["A","B"],["C"],["B","C"],["D"]], friends = [[1,2],[0,3],[0,3],[1,2]], id = 0, level = 1
输出：["B","C"] 
解释：
你的 id 为 0 ，你的朋友包括：
id 为 1 -> watchedVideos = ["C"] 
id 为 2 -> watchedVideos = ["B","C"] 
你朋友观看过视频的频率为：
B -> 1 
C -> 2
```
示例 2：
```
输入：watchedVideos = [["A","B"],["C"],["B","C"],["D"]], friends = [[1,2],[0,3],[0,3],[1,2]], id = 0, level = 2
输出：["D"]
解释：
你的 id 为 0 ，你朋友的朋友只有一个人，他的 id 为 3 . 

```

提示：
+ ```n == watchedVideos.length == friends.length```
+ ```2 <= n <= 100```
+ ```1 <= watchedVideos[i].length <= 100```
+ ```1 <= watchedVideos[i][j].length <= 8```
+ ```0 <= friends[i].length < n```
+ ```0 <= friends[i][j] < n```
+ ```0 <= id < n```
+ ```1 <= level < n```
+ ```如果 friends[i] 包含 j ，那么 friends[j] 包含 i```

### 地址
https://leetcode-cn.com/problems/get-watched-videos-by-your-friends
### 题意
>  BFS + 排序
### 思路
1. ```BFS```,获取最小距离为k的好友列表。
2. 对所获取的好友列表中每个人喜欢观看的视频进行统计，然后按照字典序和次数进行排序即可。
### 代码
```c++
typedef pair<string,int> psi;
class Solution {
public:
    vector<string> watchedVideosByFriends(vector<vector<string>>& watchedVideos, vector<vector<int>>& friends, int id, int level) {
        int n = friends.size();
        vector<bool> visit(n,false);
        vector<int> list;
        queue<int> qu;
        
        visit[id] = true;
        qu.push(id);
        while(!qu.empty()&&level > 0){
            int sz = qu.size();
            list.clear();
            
            for(int i = 0; i < sz; ++i){
                int curr = qu.front();
                qu.pop();
                
                for(auto & neg: friends[curr]){
                    if(!visit[neg]){
                        qu.push(neg);
                        visit[neg] = true;
                        list.push_back(neg);
                    }
                }
            }
            level--;
        }
        
        vector<pair<string,int>> videos;
        unordered_map<string,int> freq;
        vector<string> res;
        for(auto & p: list){
            for(auto & v: watchedVideos[p]){
                freq[v]++;
            }
        }
        for(auto & it : freq){
            videos.push_back(make_pair(it.first,it.second));
        }
        sort(videos.begin(),videos.end(),[](const psi & a,const psi & b){
           if(a.second == b.second){
               return a.first < b.first;
           } 
           return a.second < b.second;
        });
        for(auto & v : videos){
            res.push_back(v.first);
        }
        
        return res;
    }
};
```

## 5306. 让字符串成为回文串的最少插入次数
### 题目
给你一个字符串 ```s``` ，每一次操作你都可以在字符串的任意位置插入任意字符。请你返回让 ```s``` 成为回文串的 最少操作次数 。

「回文串」是正读和反读都相同的字符串。

 

示例 1：
```
输入：s = "zzazz"
输出：0
解释：字符串 "zzazz" 已经是回文串了，所以不需要做任何插入操作。
```
示例 2：
```
输入：s = "mbadm"
输出：2
解释：字符串可变为 "mbdadbm" 或者 "mdbabdm" 。
```
示例 3：
```
输入：s = "leetcode"
输出：5
解释：插入 5 个字符后字符串变为 "leetcodocteel" 。
```
示例 4：
```
输入：s = "g"
输出：0
```
示例 5：
```
输入：s = "no"
输出：1
```

提示：

+ ```1 <= s.length <= 500```
+ s 中所有字符都是小写字母。


### 地址
https://leetcode-cn.com/problems/minimum-insertion-steps-to-make-a-string-palindrome
### 题意
>  dp
### 思路
1.  本题变形的各种```dp```已经出现过很多次了，主要是那几个变形要熟悉：
$$
dp[i][j] = min(dp[i+1][j],dp[i][j-1]) + 1 \\
dp[i][j] = min(dp[i][j],dp[i+1][j-1]) \quad if(s[i] == s[j])
$$
2. 熟练掌握几个```dp```的变形，本质还是一样的变换。
### 代码
```c++
class Solution {
public:
    int minInsertions(string s) {
        int n = s.size();
        vector<vector<int>> dp(n,vector<int>(n,0));
        
        /*intial*/
        for(int i = 1; i < n; ++i){
            for(int j = 0; j+i < n; ++j){
                dp[j][j+i] = min(dp[j][j+i-1],dp[j+1][j+i]) + 1;
                if(s[j] == s[j+i]){
                    dp[j][j+i] = min(dp[j][j+i],dp[j+1][j+i-1]);
                }
            }
        }
        
        return dp[1][n];
    }
};
```