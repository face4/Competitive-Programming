#include<iostream>
using namespace std;

// 各月の日数(1-origin)
int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// うるう年の判定
bool isLeap(int x){
    if(x%4 == 0 && x%100 != 0)  return true;
    if(x%400 == 0) return true;
    return false;
}

// 1/1/1 -> y/m/d の経過日数
int pastdays(int y, int m, int d){
    if(m <= 2)  y--, m += 12;
    return 365*y + y/4 - y/100 + y/400 + (306*(m+1))/10 + d - 429;
}

// month, dayを受け取り1/1からの経過日数を返す
// だいぶ雑なので、修正が必要かもしれない(うるう年を完全に無視しているので.)
int mdTodays(int m, int d){
    int ret = 0;
    for(int i = 1; i < m; i++)  ret += days[i];
    ret += d;
    return ret;
}

int main(){
    return 0;
}