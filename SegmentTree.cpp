#include<iostream>
#include<vector>
#include<climits>
using namespace std;

// 何も考えずにコンストラクタに元配列(vector)を入れればよい
// クエリurry(a, b)は区間[a, b)に対応
// 配列の末尾を区間に含めたい場合はquery(0, ***n+1***)として呼ばなければいけないことに注意
/*                          */
const int INF = 1<<30;

struct STmin{
private:
    int n;
    vector<int> dat;
public:
    STmin(vector<int> ini){
        int siz = ini.size();
        n = 1;
        while(n < siz)   n *= 2;
        dat.resize(2*n-1, INF);
        for(int i = 0; i < siz; i++)    dat[n - 1 + i] = ini[i];
        for(int i = n-2; i >= 0; i--)   dat[i] = min(dat[2*i+1], dat[2*i+2]);
    }

    void update(int x, int val){
        x += (n-1);
        dat[x] = val;
        while(x > 0){
            x = (x-1)/2;
            node[x] = min(node[2*x+1], node[2*x+2]);
        }
    }

    // focus on k-th node, who controls [l, r)
    int query(int a, int b, int k = 0, int l = 0, int r = -1){
        if(r < 0)   r = n;
        if(r <= a || b <= l)    return INF;
        if(a <= l && r <= b)    return dat[k];

        int lx = query(a, b, 2*k+1, l, (l+r)/2);
        int rx = query(a, b, 2*k+2, (l+r)/2, r);
        return min(lx, rx);
    }
};

struct STmax{
private:
    int n;
    vector<int> dat;
public:
    STmax(vector<int> ini){
        int siz = ini.size();
        n = 1;
        while(n < siz)   n *= 2;
        dat.resize(2*n-1, -INF);
        for(int i = 0; i < siz; i++)    dat[n - 1 + i] = ini[i];
        for(int i = n-2; i >= 0; i--)   dat[i] = max(dat[2*i+1], dat[2*i+2]);
    }

    void update(int x, int val){
        x += (n-1);
        dat[x] = val;
        while(x > 0){
            x = (x-1)/2;
            node[x] = max(node[2*x+1], node[2*x+2]);
        }
    }
    
    // focus on k-th node, who controls [l, r)
    int query(int a, int b, int k = 0, int l = 0, int r = -1){
        if(r < 0)   r = n;
        if(r <= a || b <= l)    return -INF;
        if(a <= l && r <= b)    return dat[k];

        int lx = query(a, b, 2*k+1, l, (l+r)/2);
        int rx = query(a, b, 2*k+2, (l+r)/2, r);
        return max(lx, rx);
    }
};

int main(){

}