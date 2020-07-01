#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <map>
#include <limits.h>

using std::vector;
using std::cin;
using std::cout;
using namespace std;

typedef pair<int,int> pii;
struct FlowEdge
{
    int from;
    int to;
    int flow;
    int capbility;
    FlowEdge(int v,int w,int capbility){
        this->from = v;
        this->to = w;
        this->flow = 0;
        this->capbility = capbility;
    }
};

class FlowGraph{
private:
    map<pii,FlowEdge *> edgs;
    unordered_map<int, set<int> > adj; 
    unordered_set<int> visit;
    unordered_map<int,int> edgeTo;
    
    int others(FlowEdge * e,int v){
        if(!e) return -1;
        if(v == e->from) return e->to;
        else if(v == e->to) return e->from;
    }

    bool addResidualTo(FlowEdge * e,int to,int delta){
        if(!e) return false;
        if(e->from == to) e->flow -= delta;
        else if(e->to == to) e->flow += delta;
        return true;
    }

    int residualTo(FlowEdge * e,int to){
        if(!e) return -1;
        if(e->to == to) return e->capbility-e->flow;
        else if(e->from == to) return e->flow;
        return 0;
    }

public:
    FlowEdge * getEdge(int from,int to){
        pair<int,int> forward = make_pair(from,to);
        pair<int,int> backward = make_pair(to,from);

        if(this->edgs.count(forward)) return this->edgs[forward];
        else if(this->edgs.count(backward)) return this->edgs[backward];
        else return NULL;
    }

    bool addEdges(FlowEdge * e){
        this->adj[e->from].insert(e->to);
        this->adj[e->to].insert(e->from);
        this->edgs[make_pair(e->from,e->to)] = e;
        return true;
    }

    bool addResidualToEdge(int from,int to,int delta){
        FlowEdge * edge =  getEdge(from,to);
        if(!edge) return false;
        return addResidualTo(edge,to,delta);
    }

    int residualToEdge(int from,int to){
        FlowEdge * edge =  getEdge(from,to);
        if(!edge) return false;
        return residualTo(edge,to);
    }
    
    bool augmentPath(int s,int t){
        queue<int> qu;

        this->visit.insert(s);
        qu.push(s);
        while(!qu.empty()){
            int curr = qu.front();
            qu.pop();

            if(curr == t) break;
            for(auto v : this->adj[curr]){
                if(this->visit.count(v) || residualToEdge(curr,v) <= 0) continue;
                this->visit.insert(v);
                this->edgeTo[v] = curr;
            }
        }

        return this->visit.count(t) != 0;
    }

    int maxFlow(int s,int t){
        int value = 0;

        this->visit.clear();
        this->edgeTo.clear();
        while(augmentPath(s,t)){
            cout<<"get the right paht:"<<endl;
            int bottoleneck = INT_MAX;
            for(int v = t; v != s; v = this->edgeTo[v]){
                bottoleneck = min(bottoleneck,residualToEdge(this->edgeTo[v],v));
            }
            for(int v = t; v != s; v = this->edgeTo[v]){
                addResidualToEdge(this->edgeTo[v],v,bottoleneck);
            }
            value += bottoleneck;
            this->edgeTo.clear();
            this->visit.clear();
        }
        return value;
    }

    bool inCut(int v){
        return visit.count(v);
    }
};


FlowGraph read_data() {
    int vertex_count, edge_count;
    std::cin >> vertex_count >> edge_count;
    FlowGraph graph;
    for (int i = 0; i < edge_count; ++i) {
        int u, v, capacity;
        std::cin >> u >> v >> capacity;
        graph.addEdges(new FlowEdge(u - 1, v - 1, capacity));
    }
    for(int i = 1; i < vertex_count; ++i){
        graph.addEdges(new FlowEdge(i, vertex_count, 10000));
    }
    cout<<graph.maxFlow(0,vertex_count)<<endl;
    return graph;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    FlowGraph graph = read_data();
    return 0;
}
