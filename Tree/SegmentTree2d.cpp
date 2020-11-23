// 噂によるとMLEするらしい
#include<iostream>
#include<vector>
#include<climits>
using namespace std;

const int INF = INT_MAX;

struct seg2d{
    int h, w;
    vector<vector<int>> node;
    seg2d(){}
    seg2d(vector<vector<int>> &v){
        int hsiz = v.size(), wsiz = v[0].size();
        h = w = 1;
        while(h < hsiz)    h *= 2;
        while(w < wsiz)    w *= 2;
        node.resize(2*h-1, vector<int>(2*w-1, INF));
        init(hsiz, wsiz, v);
    }
    void init(int hsiz, int wsiz, vector<vector<int>> &v){
        for(int i = 0; i < hsiz; i++){
            for(int j = 0; j < wsiz; j++){
                node[h-1+i][w-1+j] = v[i][j];
            }
        }
        for(int i = 2*h-2; i > h-2; i--){
            for(int j = w-2; j >= 0; j--){
                node[i][j] = min(node[i][2*j+1], node[i][2*j+2]);
            }
        }
        for(int i = h-2; i >= 0; i--){
            for(int j = 0; j < 2*w-1; j++){
                node[i][j] = min(node[2*i+1][j], node[2*i+2][j]);
            }
        }
    }
    int query(int li, int lj, int ri, int rj){
        return query_h(li, lj, ri, rj, 0, h, 0);
    }
    int query_h(int li, int lj, int ri, int rj, int l, int r, int k){
        if(ri <= l || r <= li)  return INF;
        if(li <= l && r <= ri)  return query_w(lj, rj, 0, w, k, 0);
        int lx = query_h(li,lj,ri,rj,l,(l+r)/2,2*k+1);
        int rx = query_h(li,lj,ri,rj,(l+r)/2,r,2*k+2);
        return min(lx, rx);
    }
    int query_w(int lj, int rj, int l, int r, int i, int k){
        if(rj <= l || r <= lj)  return INF;
        if(lj <= l && r <= rj)  return node[i][k];
        int lx = query_w(lj,rj,l,(l+r)/2,i,2*k+1);
        int rx = query_w(lj,rj,(l+r)/2,r,i,2*k+2);
        return min(lx, rx);
    }
};

int main(){
    int r, c, q;
    while(cin >> r >> c >> q, r+c+q){
        vector<vector<int>> v(r, vector<int>(c));
        for(int i = 0; i < r; i++){
            for(int j = 0; j < c; j++){
                cin >> v[i][j];
            }
        }
        seg2d seg(v);
        while(q-- > 0){
            int li, lj, ri, rj;
            cin >> li >> lj >> ri >> rj;
            cout << seg.query(li,lj,ri+1,rj+1) << endl;
        }
    }
    return 0;
}