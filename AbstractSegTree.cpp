#include<iostream>
#include<vector>
#include<climits>
using namespace std;

template<typename T, typename F>
struct Seg{
private:
    vector<T> node;
    int n;
    F f;
    T def;

public:
    Seg(int siz, T d, F f) : def(d), f(f) {
        n = 1;
        while(n < siz)  n *= 2;
        node.resize(2*n-1, def);
    }
    Seg(vector<T> v, T d, F f) : def(d), f(f){
        n = 1;
        while(n < v.size())  n *= 2;
        node.resize(2*n-1, def);
        for(int i = 0; i < v.size(); i++)   node[n-1+i] = v[i];
        for(int i = n-2; i >= 0; i--)   node[i] = f(node[2*i+1], node[2*i+2]);
    }

    void update(int x, T val){
        x += n-1;
        node[x] = val; /* ! */
        while(x){
            x = (x-1)/2;
            node[x] = f(node[2*x+1], node[2*x+2]);
        }
    }

    T query(int a, int b){
        int L = a+n-1, R = b+n-1;
        T lx = def, rx = def;
        while(L < R){
            if((R&1) == 0)  rx = f(node[--R], rx);
            if((L&1) == 0)  lx = f(lx, node[L++]);
            L >>= 1, R >>= 1;
        }
        return f(lx, rx);
    }
};

int main(){
    int n, q;
    cin >> n >> q;
    auto f = [](int x, int y){return min(x,y);};
    Seg<int, decltype(f)> stmin(n, INT_MAX, f);
    while(q-- > 0){
        int x, y, z;
        cin >> x >> y >> z;
        if(x == 0)  stmin.update(y, z);
        if(x == 1)  cout << stmin.query(y, z+1) << endl;
    }
    return 0;
}