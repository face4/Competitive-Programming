#include<iostream>
#include<algorithm>
using namespace std;

#define MAX_N 500000
int n, k;
int rnk[MAX_N+1], tmp[MAX_N+1];

bool compare_sa(int i, int j){
    if(rnk[i] != rnk[j])  return rnk[i] < rnk[j];
    int ri = i+k <= n ? rnk[i+k] : -1;
    int rj = j+k <= n ? rnk[j+k] : -1;
    return ri < rj;
}

void construct_sa(string s, int *sa){
    n = s.length();
    for(int i = 0; i <= n; i++){
        sa[i] = i;
        rnk[i] = i < n ? s[i] : -1;
    }
    for(k = 1; k <= n; k *= 2){
        sort(sa, sa+n+1, compare_sa);
        // 新しくrnk(k文字目までの比較における順序)を振り直す
        tmp[sa[0]] = 0;
        for(int i = 1; i <= n; i++){
            tmp[sa[i]] = tmp[sa[i-1]] + (compare_sa(sa[i-1], sa[i]) ? 1 : 0);
        }
        for(int i = 0; i <= n; i++) rnk[i] = tmp[i];
    }
}

void construct_lcp(string s, int *sa, int *lcp){
    int n = s.length();
    for(int i = 0; i <= n; i++) rnk[sa[i]] = i;

    int h = 0;
    lcp[0] = 0;
    for(int i = 0; i < n; i++){
        int j = sa[rnk[i]-1];
        if(h > 0)   h--;
        for(; j+h < n && i+h < n; h++){
            if(s[j+h] != s[i+h])    break;
        }
        lcp[rnk[i]-1] = h;
    }
}

bool contain(string s, int *sa, string t){
    int l = 0, r = s.length();
    while(r-l > 1){
        int mid = (l+r)/2;
        if(s.compare(sa[mid], t.length(), t) < 0)   l = mid;
        else                                        r = mid;
    }
    return s.compare(sa[r], t.length(), t) == 0;
}

int main(){
    return 0;
}