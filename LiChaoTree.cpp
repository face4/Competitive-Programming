#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long ll;

struct line{
    ll a, b;
    bool operator==(const line other)const{
        return a==other.a && b==other.b;
    }
};

ll f(line l, ll x){
    return l.a*x + l.b;
}

const ll INF = 1ll<<62;

struct LiChaoTree{
    int n;
    vector<ll> xs;
    vector<line> v;
    line tmp{0, INF};
    LiChaoTree(vector<ll> x) : xs(x){
        n = 1;
        while(n < xs.size())  n *= 2;
        while(xs.size() < n)    xs.push_back(x.back());
        v.resize(2*n+1, tmp);
    }
    // 直線追加
    void add_line(line p, int k=0, int l=0, int r=-1){
        if(r < 0)   r = n;
        int m = (l+r)/2;
        if(v[k] == tmp){
            v[k] = p;
            return;
        }
        ll lx = xs[l], mx = xs[m], rx = xs[r-1];
        bool left = f(p,lx) < f(v[k], lx);
        bool mid = f(p,mx) < f(v[k], mx);
        bool right = f(p,rx) < f(v[k], rx);
        if(left == right){
            if(left)    v[k] = p;
            return;
        }
        if(mid){
            swap(v[k], p);
        }
        // v[k]とpが交わっている部分について更新していくと考えるとわかりやすい
        if(left != mid){
            add_line(p, 2*k+1, l, m);
        }else{
            add_line(p, 2*k+2, m, r);
        }
    }
    // 線分追加(ボトムアップ) [a, b)
    void add_segment(line p, int a, int b){
        int L = a+n-1, R = b+n-1;   // 葉ノードのindex
        int a0 = a, b0 = b;
        int blocksize = 1;
        while(L < R){
            if((R&1) == 0){
                R -= 1;
                b0 -= blocksize;
                add_line(p, R, b0, b0+blocksize);
            }
            if((L&1) == 0){
                add_line(p, L, a0, a0+blocksize);
                L += 1;
                a0 += blocksize;
            }
            L >>= 1, R >>= 1;
            blocksize <<= 1;
        }
    }
    ll query(int k){
        ll x = xs[k];
        k += n-1;
        ll ret = INF;
        while(true){
            if(!(v[k]==tmp)) ret = min(ret, f(v[k], x));
            if(k==0)    break;
            k = (k-1)/2;
        }
        return ret;
    }
};

int main(){
    
}