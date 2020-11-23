// yukicoder No.129でverify
// dpテーブルをllでやると要素数10000でMLEになってしまうので気を付けること.
#include<iostream>
#include<vector>
using namespace std;

struct Combination{
    int n;
    vector<vector<int>> dp;

    Combination(int i){
        n = i;
        dp = vector<vector<int>>(n+1, vector<int>(n+1, 0));
        constructTriangle();
    }

    void constructTriangle(){
        dp[0][0] = 1;
        for(int i = 1; i <= n; i++){
            dp[i][0] = dp[i-1][0];
            for(int j = 1; j <= i; j++){
                // modを取るならここで!
                dp[i][j] = dp[i-1][j] + dp[i-1][j-1];
            }
        }
    }

    // return aCb
    int getCombination(int a, int b){
        return dp[a][b];
    }
};