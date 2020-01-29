#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

typedef pair<int,int> pii;
struct LowLink{
    int n, k, rootCnt;
    vector<int> ord, low, parent;
    vector<bool> vis;
    vector<vector<int>> v;
    vector<pii> edge;

    LowLink(int n) : n(n){
        ord.resize(n);
        low.resize(n);
        parent.resize(n);
        vis.resize(n, 0);
        v.resize(n);
    }

    void add_edge(int a, int b){
        edge.push_back({a, b});
        v[a].push_back(b);
        v[b].push_back(a);
    }

    void dfs(int x, int p, int &k){
        parent[x] = p;
        ord[x] = low[x] = k++;
        vis[x] = true;
        for(int j : v[x]){
            if(vis[j]){
                if(j != p)  low[x] = min(low[x], ord[j]);
            }else{
                if(x == 0)  rootCnt++;
                dfs(j, x, k);
                low[x] = min(low[x], low[j]);
            }
        }
    }

    void build(){
        k = 0;
        rootCnt = 0;
        dfs(0, -1, k);
    }

    vector<pii> bridge(){
        vector<pii> ret;
        for(pii p : edge){
            int x = p.first, y = p.second;
            if(ord[x] > ord[y]) swap(x, y);
            if(ord[x] < low[y]) ret.push_back(p);
        }
        return ret;
    }

    vector<int> articulationPoint(){
        vector<int> ret;
        if(rootCnt > 1) ret.push_back(0);
        for(int i = 1; i < n; i++){
            int p = parent[i];
            if(p > 0 && low[i] >= ord[p])   ret.push_back(p);
        }
        sort(ret.begin(), ret.end());
        ret.erase(unique(ret.begin(),ret.end()),ret.end());
        return ret;
    }
};

int main(){
    int n, m;
    cin >> n >> m;
    LowLink l(n);
    while(m--){
        int u, v;
        cin >> u >> v;
        l.add_edge(u, v);
    }
    l.build();
    vector<int> res = l.articulationPoint();
    for(int i : res)    cout << i << endl;
    return 0;
}