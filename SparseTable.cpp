#include<iostream>
#include<vector>
using namespace std;

// indexではなく実値を返す
template<class T, class F>
struct SparseTable{
    vector<vector<T>> table;
    vector<int> log_table;
    F f;
    SparseTable(const vector<T> &v, F ff):f(ff){
        int n = v.size();
        int bit = 0;
        while((1<<bit) <= n)    bit++;
        table.resize(bit);
        table[0] = v;
        for(int k = 1; k < bit; k++){
            table[k].resize(n-(1<<k)+1);    // メモリ節約
            for(int i = 0; i+(1<<k) <= n; i++){
                table[k][i] = f(table[k-1][i], table[k-1][i+(1<<(k-1))]);
            }
        }
        log_table.resize(n+1);
        for(int i = 2; i <= n; i++) log_table[i] = log_table[i>>1]+1;
    }

    // 0-indexed, [a, b]
    T query(int a, int b){
        int d = b-a+1;
        int k = log_table[d];
        return f(table[k][a], table[k][b-(1<<k)+1]);
    }
};

int main(){
    int n, q;
    scanf("%d %d", &n, &q);
    vector<int> v(n);
    for(int i = 0; i < n; i++)  scanf("%d", v.begin()+i);
    auto f = [](int i, int j)->int{
        return min(i, j);
    };
    SparseTable<int, decltype(f)> s(v, f);
    while(q--){
        int l, r;
        scanf("%d %d", &l, &r);
        printf("%d\n", s.query(l, r-1));
    }
    return 0;
}

// verified on https://judge.yosupo.jp/problem/staticrmq