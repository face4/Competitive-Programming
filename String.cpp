#include<iostream>
#include<cstring>
#include<vector>
using namespace std;

bool isPalindrome(string s){
    int n = s.length();
    for(int i = 0; i < n/2; i++){
        if(s[i] != s[n-1-i])    return false;
    }
    return true;
}

// 編集距離(レーヴェンシュタイン距離)を求める.
// O(a.length() * b.length())
// https://mathwords.net/hensyukyori
int LevenDis(string a, string b){
    int alen = a.length(), blen = b.length();
    int dp[alen+1][blen+1];

    for(int i = 0; i < alen+1; i++) dp[i][0] = i;
    for(int j = 0; j < blen+1; j++) dp[0][j] = j;

    for(int i = 1; i < alen+1; i++){
        for(int j = 1; j < blen+1; j++){
            dp[i][j] = min(dp[i-1][j]+1, min(dp[i][j-1]+1, dp[i-1][j-1] + (a[i-1] != b[j-1])));
        }
    }

    return dp[alen][blen];
}

// Longest Common Substring[Subsequence]の長さを求める.
// a, bがある程度長いと配列dpのメモリが確保されなくなるので、グローバル変数
// として用意するかstacitで宣言するなど何らかの対策が必要
int getLCSlen(string a, string b){
    int dp[a.length()][b.length()];
    int ret = 0;

    for(int i = 0; i < a.length(); i++){
        for(int j = 0; j < b.length(); j++){
            dp[i][j] = 0;
        }
    }

    for(int j = 0; j < b.length(); j++) if(a[0] == b[j])    dp[0][j] = 1;
    for(int i = 0; i < a.length(); i++) if(a[i] == b[0])    dp[i][0] = 1;
    
    // add these if you want to get longest common subsequence
    // for(int i = 1; i < a.length(); i++) dp[i][0] = max(dp[i][0], dp[i-1][0]);
    // for(int j = 1; j < b.length(); j++) dp[0][j] = max(dp[0][j], dp[0][j-1]);


    for(int i = 1; i < a.length(); i++){
        for(int j = 1; j < b.length(); j++){
            if(a[i] == b[j]){
                dp[i][j] = dp[i-1][j-1]+1;
                ret = max(ret, dp[i][j]);
            }
            // add these if you want to get longest common subsequence
            // dp[i][j] = max(dp[i][j], max(dp[i-1][j], dp[i][j-1]));
            // ret = max(ret, dp[i][j]);
        }
    }
    return ret;
}

// strをdelで区切る.いずれdelがstringでも大丈夫なように作り変える.
vector<string> split(string str, char del = ' '){
    vector<string> ret;
    string cutoff = "";
    for(int i = 0; i < str.length(); i++){
        if(str[i] == del){
            if(cutoff != "")    ret.push_back(cutoff);
            cutoff = "";
        }else{
            cutoff += str[i];
        }
    }
    if(cutoff != "")    ret.push_back(cutoff);
    return ret;
}

// strの接頭辞がpreかどうかを判別する.
bool startsWith(string str, string pre){
    int s = str.length(), p = pre.length();
    if(s < p)   return false;

    int j;
    for(j = 0; j < p; j++){ 
        if(str[j] != pre[j])  break;
    }

    return j == p;
}

// strがpreを含むかどうかを判別する.
// findとかに名前を変えて位置を返すようにした方がいいかもしれない.
bool contains(string str, string pre){
    int s = str.length(), p = pre.length();
    if(s < p)   return false;

    for(int i = 0; i <= s - p; i++){
        int j;
        for(j = 0; j < p; j++){ 
            if(str[i+j] != pre[j])  break;
        }
        if(j == p)  return true;
    }

    return false;
}

/* suffix array O(n logn logn) */
#define MAX_N 1000000
int n, k;
int rnk[MAX_N+1];
int tmp[MAX_N+1];

bool compare_sa(int i, int j){
    if(rnk[i] != rnk[j]){
        return rnk[i] < rnk[j];
    }else{
        int ri = i+k <= n ? rnk[i+k] : -1;
        int rj = j+k <= n ? rnk[j+k] : -1;
        return ri < rj;
    }
}

void construct_sa(string s, int *sa){
    n = s.length();
    for(int i = 0; i <= n; i++){
        sa[i] = i;
        rnk[i] = i < n ? s[i] : -1;
    }
    for(k = 1; k <= n; k *= 2){
        sort(sa, sa+n+1, compare_sa);
        tmp[sa[0]] = 0;
        for(int i = 1; i <= n; i++){
            tmp[sa[i]] = tmp[sa[i-1]] + (compare_sa(sa[i-1], sa[i]) ? 1 : 0);
        }
        for(int i = 0; i <= n; i++){
            rnk[i] = tmp[i];
        }
    }
}

bool contain(string s, int *sa, string t){
    int a = 0, b = s.length();
    while(b - a > 1){
        int c = (a+b)/2;
        if(s.compare(sa[c], t.length(), t) < 0) a = c;
        else    b = c;
    }
    return s.compare(sa[b], t.length(), t) == 0;
}
/*  */

int main(){
    cout << startsWith("0010","01") << endl;
    return 0;
}