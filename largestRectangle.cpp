// 最大長方形を求める.AOJ0092に基づいているので一般化の必要がある.

#include<iostream>
#include<stack>
using namespace std;

int main(){
    int n;
    while(cin >> n, n){
        char mat[n][n];
        int dp[n][n];
        
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                cin >> mat[i][j];
            }
        }
        
        for(int i = 0; i < n; i++)  dp[0][i] = (mat[0][i] == '.');
        for(int i = 1; i < n; i++){
            for(int j = 0; j < n; j++){
                if(mat[i][j] == '.')    dp[i][j] = dp[i-1][j]+1;
                else                    dp[i][j] = 0;
            }
        }
        
        int ans = -1;
        for(int i = 0; i < n; i++){
            // pair<left end, height>
            stack<pair<int,int>> s;
            for(int j = 0; j < n; j++){
                if(s.empty()){
                    s.push({j, dp[i][j]});
                }else if(dp[i][j] > s.top().second){
                    s.push({j, dp[i][j]});
                }else if(dp[i][j] == s.top().second){
                    // do nothing.
                }else if(dp[i][j] < s.top().second){
                    int left;
                    while(!s.empty() && dp[i][j] < s.top().second){
                        pair<int,int> now = s.top(); s.pop();
                        // make rectangle
                        ans = max(ans, (j-now.first)*(now.second));
                        left = now.first;
                    }
                    s.push({left, dp[i][j]});
                }
            }
            
            while(!s.empty()){
                pair<int,int> now = s.top(); s.pop();
                ans = max(ans, (n-now.first)*(now.second));
            }
        }
        
        cout << ans << endl;
    }
    
    return 0;
}
