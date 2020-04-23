#include<vector>
#include<iostream>
#include<map>
#include<set>
#include<string>
#include<stack>
#include<queue>
#include<algorithm>

using namespace std;

class Nfa{
public:
    Nfa(){
        this->regexpr = "";
        this->m = 0;
    }

    bool build(string re){
        this->m = re.size();
        this->regexpr = re;
        this->graph.clear();
        stack<int> ops;

        for(int i = 0; i < re.size(); ++i){
            int lp = i;
            if(re[i] == '('||re[i] == '|'){
                ops.push(i);
            }else if(re[i] == ')'){
                if(ops.empty()) return false;
                if(re[ops.top()] == '|'){
                    stack<int> curr;
                    while(!ops.empty()&&re[ops.top()] == '|'){
                        curr.push(ops.top());
                        ops.pop();
                    }
                    if(ops.empty()||re[ops.top()] != '(') return false;
                    lp = ops.top();
                    ops.pop();

                    while(!curr.empty()){
                        this->addEdge(lp,curr.top()+1);
                        this->addEdge(curr.top(),i);
                        curr.pop();
                    }
                }else if(re[ops.top()] == '('){
                    lp = ops.top();
                    ops.pop();
                }else return false;
            }
            
            if(i+1 < this->m && re[i+1] == '*'){
                this->addEdge(i+1,lp);
                this->addEdge(lp,i+1);
            }
            if(i+1 < this->m && re[i+1] == '+'){
                this->addEdge(i+1,lp);
            }
            if(re[i] == '(' || re[i] == '*' || 
               re[i] == ')' || re[i] == '+'){
                this->addEdge(i,i+1);
            }
        }

        if(!ops.empty()) return false;
        return true;
    }

     bool debug(){
        for(int i = 0;i < this->m; ++i){
            if(this->graph.count(i)){
                for(auto v : this->graph[i]){
                    cout<<i<<"-->"<<v<<endl;
                }
            }
        }
        return true;
    }

    bool isMatch(string target){
        set<int> marked;
        vector<int> pc;

        dfs(0,marked);
        for(auto v : marked){
            pc.push_back(v);
        }
        for(int i = 0; i < target.size(); ++i){
            vector<int> matched;
            for(auto v : pc){
                if(v == this->m) continue;
                if(this->regexpr[v] == target[i] || this->regexpr[v] == '.'){
                    matched.push_back(v+1);
                }
            }

            marked.clear();
            pc.clear();
            for(auto v : matched){
                dfs(v,marked);
            }
            for(auto v : marked){
                pc.push_back(v);
            }
        }

        for(auto v : pc){
            if(v == this->m) return true;
        }
        return false;
    }

private:
    bool dfs(int curr,set<int> & marked){
        marked.insert(curr);
        for(auto v : graph[curr]){
            if(marked.count(v)) continue;
            dfs(v,marked);
        }
        return true;
    }

    bool addEdge(int v,int w){
        this->graph[v].push_back(w);
        return true;
    }

    string regexpr;
    map<int,vector<int>> graph;
    int m;
};

typedef pair<int,int> pii;
static bool cmp(vector<int> & a,vector<int> & b){
    if(a[0] == b[0]) return a[1] < b[1];
    return a[0] < b[0];
}

int AllTime(vector<vector<int>> & task){
    int res = 0;
    int wait = 0;
    int curr = 0;
    int mod = 1e9+7;
    priority_queue<int,vector<int>,greater<int>> pq;
    sort(task.begin(),task.end(),cmp);
    
    curr = task[0][0];
    for(int i = 0; i < task.size(); ++i){
        if(pq.empty() || task[i][0] <= curr){
            pq.push(task[i][1]);
            continue;
        }

        if(task[i][0] > curr){
            while(!pq.empty() && curr + pq.top() <= task[i][0]){
                res = (res + pq.top()*(pq.size()-1))%mod;
                curr = curr + pq.top();
                pq.pop();
            }
            if(!pq.empty()){
                wait = task[i][0] - curr;
                int rest = curr + pq.top() - task[i][0];
                res = (res + wait*(pq.size()-1))%mod;
                pq.pop();
                pq.push(rest);
            }
            curr = task[i][0];
            pq.push(task[i][1]);
        }
    }

    while(!pq.empty()){
        res = (res + pq.top()*(pq.size()-1))%mod;
        pq.pop();
    }

    return res;
}

int main(){
    vector<vector<int>> task;
    task.push_back({0,5});
    task.push_back({1,2});
    //task.push_back({1,2});
    task.push_back({2,1});
    cout<<AllTime(task);
}