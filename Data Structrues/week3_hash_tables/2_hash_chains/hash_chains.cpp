#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <list>

using std::string;
using std::vector;
using std::cin;
using namespace std;

struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor {
    int bucket_count;
    // store all strings in one vector
    vector<list<string>> elems;
    vector<set<string>> count;
    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count) {
         elems = vector<list<string>>(this->bucket_count);
         count = vector<set<string>>(this->bucket_count);
    }

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    void processQuery(const Query& query) {
        if (query.type == "check") {
            if(elems[query.ind].size() == 0){
                cout<<endl;
            }else{
                vector<string> arr;
                for(auto s : elems[query.ind]){
                    cout<<s<<" ";
                }
                cout<<endl;
            }
        } else {
            int idx = hash_func(query.s);
            if(query.type == "find"){
                if(count[idx].count(query.s)){
                    cout<<"yes"<<endl;
                }else{
                    cout<<"no"<<endl;
                }
            }else if (query.type == "add") {
                if(count[idx].count(query.s)) return;
                elems[idx].push_front(query.s);
                count[idx].insert(query.s);
            } else if (query.type == "del") {
                if(!count[idx].count(query.s)) return;
                elems[idx].remove(query.s);
                count[idx].erase(query.s);
            }
        }
    }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
