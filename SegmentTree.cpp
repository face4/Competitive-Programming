#include<iostream>
#include<vector>
#include<climits>
using namespace std;

/*                          */
const int INF = 1<<21;

class SegmentTree{
public:
    int n;
    vector<int> dat;
    
    SegmentTree(vector<int> v){
        int size = v.size();
        n = 1;
        while(n < size) n *= 2;
        dat.resize(2*n - 1, INF);
    
        for(int i = 0; i < size; i++)   dat[i+n-1] = v[i];
        for(int i = n-2; i >= 0; i--)   dat[i] = min(dat[2*i+1], dat[2*i+2]);
    }

    void update(int x, int val){
        x += n-1;
        dat[x] = val;
        while(x > 0){
            x = (x-1) / 2;
            dat[x] = min(dat[2*x+1], dat[2*x+2]);
        }
    }

    // [a, b)の最小値を求める
    // 外からはquery(a, b, 0, 0, n)として呼ぶ
    int query(int a, int b, int k, int l, int r){
        // [a, b)と[l, r)が交わらない
        if(r <= a || b <= l)    return INT_MAX;

        // [a, b)が[l, r)を完全に含む
        if(a <= l && r <= b)    return dat[k];
        else{
            int vl = query(a, b, 2*k+1, l, (l+r)/2);
            int vr = query(a, b, 2*k+2, (l+r)/2, r);
            return min(vl, vr);
        }
    }
};

int main(){

}