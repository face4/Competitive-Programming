#include<iostream>
#include<vector>
#include<cstring>
#include<queue>
using namespace std;

#define maxv 100

struct edge{
    int to, cap, rev;
};

vector<edge> G[maxv];
int dist[maxv];
int iter[maxv]; // どこまで調べ終わったか

void add_edge(int from, int to, int cap){
    G[from].push_back(edge({to, cap, (int)G[to].size()}));
    G[to].push_back(edge({from, 0, (int)G[from].size()-1}));
}

void bfs(int s){
    memset(dist, -1, sizeof(dist));
    queue<int> q;
    dist[s] = 0;
    q.push(s);
    while(!q.empty()){
        int x = q.front();  q.pop();
        for(edge e : G[x]){
            int next = e.to;
            if(e.cap > 0 && dist[next] < 0){
                dist[next] = dist[x]+1;
                q.push(next);
            }
        }
    }
}

// あるパスを採用する時、使えなくなるエッジはcapが最小の1本だけである
// 次のDFSにおいてそのようなエッジまでは全く同じパスを調べてしまう
// そのような無駄を省くために調べたエッジを記憶しておく(iter)
int dfs(int v, int t, int f){
    if(v == t)  return f;
    for(int &i = iter[v]; i < G[v].size(); i++){
        edge &e = G[v][i];
        if(e.cap > 0 && dist[e.to] > dist[v]){
            int d = dfs(e.to, t, min(f, e.cap));
            if(d > 0){
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

const int INF = 1<<30;

int max_flow(int s, int t){
    int flow = 0;
    while(true){
        bfs(s);
        if(dist[t] < 0) return flow;
        memset(iter, 0, sizeof(iter));
        int f;
        while((f = dfs(s, t, INF)) > 0) flow += f;
    }
}

int main(){
    int v, e;
    cin >> v >> e;
    while(e--){
        int a, b, c;
        cin >> a >> b >> c;
        add_edge(a, b, c);
    }
    cout << max_flow(0, v-1) << endl;
    return 0;
}