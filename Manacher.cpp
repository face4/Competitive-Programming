// 未verify
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// 奇数長回文の最長半径rを返す 回文長2r-1
int manacher(string s){
    int n = s.length();
    vector<int> rad(n);
    int i = 0, j = 0;
    while(i < n){
        while(i-j >= 0 && i+j < n && s[i-j]==s[i+j])    j++;
        rad[i] = j;
        int k = 1;
        while(i-k >= 0 && i+k < n && k+rad[i-k]<j)    rad[i+k] = rad[i-k], k++;
        i += k;
        j -= k;
    }
    return *max_element(rad.begin(), rad.end());
}

// 偶数長の回文 回文長2r
int manacher2(string s){
    string t = "";
    t += s[0];
    for(int i = 1; i < s.length(); i++){
        t += "$";
        t += s[i];
    }
    s = t;
    int n = s.length();
    vector<int> rad(n);
    int i = 0, j = 0;
    while(i < n){
        while(i-j >= 0 && i+j < n && s[i-j]==s[i+j])    j++;
        rad[i] = j;
        int k = 1;
        while(i-k >= 0 && i+k < n && k+rad[i-k]<j)    rad[i+k] = rad[i-k], k++;
        i += k;
        j -= k;
    }
    int ret = 0;
    for(int i = 1; i < t.length(); i+=2)    ret = max(ret, rad[i]);
    return ret/2;
}


int main(){
    while(true){
        string s;
        cout << "String ? ";
        cin >> s;
        cout << max(manacher(s)*2-1, manacher2(s)*2) << endl;
    }
    return 0;
}