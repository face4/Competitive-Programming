#include<iostream>
#include<vector>
#include<climits>
using namespace std;

// F : T x T -> T
// G : T x E -> T
// H : E x E -> E
template<typename T, typename E, typename F, typename G, typename H>
struct SegL{
private:
    vector<T> node;
    vector<E> lazy;
    int n;
    T defVal;
    E defOp;
    F f;    // merge elements(T)
    G g;    // update element(T) 
    H h;    // merge operators(E)

public:
    SegL(int siz, T defVal, E defOp, F f, G g, H h) : defVal(defVal), defOp(defOp), f(f), g(g), h(h){
        n = 1;
        while(n < siz)  n *= 2;
        node.resize(2*n-1, defVal);
        lazy.resize(2*n-1, defOp);
    }
    SegL(vector<T> v, T defVal, E defOp, F f, G g, H h) : defVal(defVal), defOp(defOp), f(f), g(g), h(h){
        n = 1;
        while(n < v.size())  n *= 2;
        node.resize(2*n-1, defVal);
        for(int i = 0; i < v.size(); i++)   node[n-1+i] = v[i];
        for(int i = n-2; i >= 0; i--)   node[i] = f(node[2*i+1], node[2*i+2]);
    }

    void eval(int k){
        if(lazy[k] == defOp)    return;
        if(k < n-1){
            lazy[2*k+1] = h(lazy[2*k+1], lazy[k]);
            lazy[2*k+2] = h(lazy[2*k+2], lazy[k]);
        }
        node[k] = g(node[k], lazy[k]);
        lazy[k] = defOp;
    }

    void update(int a, int b, E x, int k=0, int l=0, int r=-1){
        if(r < 0)   r = n;
        eval(k);
        if(b <= l || r <= a){
            return;
        }else if(a <= l && r <= b){
            lazy[k] = h(lazy[k], x);
            eval(k);
        }else{
            update(a, b, x, 2*k+1, l, (l+r)/2);
            update(a, b, x, 2*k+2, (l+r)/2, r);
            node[k] = f(node[2*k+1], node[2*k+2]);
        }
    }

    T query(int a, int b, int k=0, int l=0, int r=-1){
        if(r < 0)   r = n;
        eval(k);
        if(b <= l || r <= a)    return defVal;
        if(a <= l && r <= b)    return node[k];
        T lx = query(a, b, 2*k+1, l, (l+r)/2);
        T rx = query(a, b, 2*k+2, (l+r)/2, r);
        return f(lx, rx);
    }
};

// DSL_2_F
// https://algo-logic.info/segment-tree/

int main(){
    int n, q;
    cin >> n >> q;
    auto f = [](int x, int y)->int{return min(x, y);};
    auto g = [](int x, int y)->int{return y==-1 ? x : y;};
    auto h = [](int x, int y)->int{return y==-1 ? x : y;};
    int defv = INT_MAX;
    int defop = -1;
    SegL<int, int, decltype(f), decltype(g), decltype(h)> seg(n, defv, defop, f, g, h);
    while(q--){
        int op;
        cin >> op;
        if(op == 0){
            int s, t, x;
            cin >> s >> t >> x;
            seg.update(s, t+1, x);
        }else{
            int s, t;
            cin >> s >> t;
            cout << seg.query(s, t+1) << endl;
        }
    }
    return 0;
}
