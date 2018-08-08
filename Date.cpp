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

int main(){
    return 0;
}