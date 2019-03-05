// 最大で2^30回まで親を辿る
// par[i][j] := j番目のnodeから2^i回親を辿ったときのnode(たどり着けない場合は-1)

#include<iostream>
#include<vector>
#include<cstring>
using namespace std;

#define NODENUM 100000

vector<int> depth(NODENUM, 0), v[NODENUM];
vector<vector<int>> par(30, vector<int>(NODENUM));
int n;

void dfs(int now, int p, int d){
    par[0][now] = p;
    depth[now] = d;
    for(int child : v[now]){
        if(child == p)  continue;
        dfs(child, now, d+1);
    }
}

void init(){
    dfs(0, -1, 0);
    for(int k = 0; k+1 < 30; k++){
        for(int i = 0; i < n; i++){
            if(par[k][i] < 0)   par[k+1][i] = -1;
            else                par[k+1][i] = par[k][par[k][i]];
        }
    }
}

int lca(int u, int v){
    // make v deeper
    if(depth[u] > depth[v]) swap(u, v);
    for(int k = 0; k < 30; k++){
        // depth(v)-depth(u) is equal to or bigger than 2^k
        if(((depth[v]-depth[u])>>k)&1){
            v = par[k][v];
        }
    }
    if(u == v)  return u;
    for(int k = 30-1; k >= 0; k--){
        if(par[k][u] != par[k][v]){
            u = par[k][u];
            v = par[k][v];
        }
    }
    return par[0][u];
}

int main(){
    cin >> n;
    int x, y;
    for(int i = 1; i < n; i++){
        cin >> x >> y;
        x--, y--;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    init();

    int q;
    cin >> q;
    while(q-- > 0){
        cin >> x >> y;
        int l = lca(--x, --y);
        cout << depth[x]-depth[l] + depth[y]-depth[l] + 1 << endl;
    }

    return 0;
}