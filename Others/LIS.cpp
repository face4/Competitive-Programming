#include<iostream>
using namespace std;

const int INF = 1<<30;
// int型配列とそのサイズを受け取り、LISの長さを返す
int getLISLen(int arr[], int n){
    int l[n];
    for(int i = 0; i < n; i++)  l[i] = INF;
    
    for(int i = 0; i < n; i++){
        *(lower_bound(l, l+n, arr[i])) = arr[i];
    }

    return (int)((lower_bound(l, l+n, INF))-l);
}

int main(){
    int a[3] = {2,1,4};
    cout << getLISLen(a, 3) << endl;
    return 0;
}