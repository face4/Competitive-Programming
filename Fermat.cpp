#include<iostream>
using namespace std;

typedef long long ll;

// a^b mod p を計算する
ll powerInMod(ll a, ll b, ll p){
    if(b == 0)  return 1;

    if(b % 2 == 0){
        ll d = powerInMod(a, b/2, p);
        return (d*d) % p;
    }else{
        return (a * powerInMod(a, b-1, p)) % p;
    }
}

// 未検証
// 組み合わせ mod pを逆元を用いて高速に求める
// pが素数である必要がある
ll nCm(ll n, ll m, ll p){
    ll ret = 1;
    
    // nCm == nC(n-m)
    if(m > n/2) m = n-m;

    for(ll i = 1; i <= m; i++){
        ret *= n-(i-1);
        ret %= p;
        ret *= powerInMod(i, p-2, p);
        ret %= p;
    }
    
    return ret;
}