//　!!! 未検証 !!!
#include<iostream>
#include<vector>
#include<climits>
using namespace std;

// 区間可算・区間和を扱う遅延セグメント木
// http://tsutaj.hatenablog.com/entry/2017/03/30/224339
/*                          */
const int INF = 1<<21;

class LazySegmentTree{
public:
    int n;
    vector<int> dat, lazy;
    
    LazySegmentTree(vector<int> v){
        int size = v.size();
        n = 1;
        while(n < size) n *= 2;
        dat.resize(2*n - 1, INF);
        lazy.resize(2*n-1, 0);
    
        for(int i = 0; i < size; i++)   dat[i+n-1] = v[i];
        for(int i = n-2; i >= 0; i--)   dat[i] = min(dat[2*i+1], dat[2*i+2]);
    }

    // k番目のノードについて遅延評価を行う
    void eval(int k, int l, int r){
        if(lazy[k] != 0){
            dat[k] += lazy[k];

            if(r-l > 1){
                // 最下段でない
                lazy[2*k+1] = lazy[k] / 2;
                lazy[2*k+2] = lazy[k] / 2;
            }
            
            lazy[k] = 0;
        }
    }

    // 区間加算
    void add(int a, int b, int x, int k=0, int l=0, int r=-1){
        if(r < 0)   r = n;

        // 範囲外
        if(b <= l || r <= a)    return;

        // 完全に被覆
        if(a <= l && r <= b){
            lazy[k] += (r - l) * x;
            eval(k, l, r);
        }
        // 部分的に被覆
        else{
            add(a, b, x, 2*k+1, l, (l+r)/2);
            add(a, b, x, 2*k+2, (l+r)/2, r);
            dat[k] = dat[2*k+1] + dat[2*k+2];
        }
    }

    // 区間和
    int getsum(int a, int b, int k=0, int l=0, int r=-1){
            if(r < 0)   r = n;

            eval(k, l, r);

            if(b <= l || r <= a)    return 0;
            if(a <= l && r <= b)    return dat[k];

            int vl = getsum(a, b, 2*k+1, l, (l+r)/2);
            int vr = getsum(a, b, 2*k+2, (l+r)/2, r);
            return vl + vr;
    }

};

int main(){

}