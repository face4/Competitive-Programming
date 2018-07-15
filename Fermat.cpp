#include<iostream>
using namespace std;

typedef long long ll;

// a^b mod p を計算する
ll calc(ll a, ll b, ll p){
    if(b == 0)  return 1;

    if(b % 2 == 0){
        ll d = calc(a, b/2, p);
        return (d*d) % p;
    }else{
        return (a * calc(a, b-1, p)) % p;
    }
}