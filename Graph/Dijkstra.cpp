#include<iostream>
#include<vector>
#include<queue>
using namespace std;

typedef long long ll;
const ll INF = 1ll<<60;

struct Edge{int to; ll cost;};

int n, m, s, t, u, v, a, b;

// distは予めINF埋めされているものとする
void dijkstra(int from, vector<vector<Edge>> &path, ll *dist){
    dist[from] = 0;
    priority_queue<pair<ll, int>> pq;

    pq.push({dist[from], from});

    while(!pq.empty()){
        pair<ll, int> now = pq.top();   pq.pop();
        ll c = -now.first;
        int pos = now.second;
        if(c > dist[pos])    continue;
        for(Edge e : path[pos]){
            if(dist[e.to] > c + e.cost){
                dist[e.to] = c + e.cost;
                pq.push({-dist[e.to], e.to});
            }
        }
    }
}

int main(){
    
}