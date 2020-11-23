#include<iostream>
#include<vector>
using namespace std;

template<typename T>
void init(vector<T> &v){
    int h = v.size();
    int w = v[0].size();
    for(int i = 0; i < h; i++){
        for(int j = 1; j < w; j++){
            v[i][j] += v[i][j-1];
        }
    }
    for(int j = 0; j < w; j++){
       for(int i = 1; i < h; i++){
           v[i][j] += v[i-1][j];
       } 
    }
}

int main(){
    auto f = [&](int i, int j, int k, int l)->int{
        return v[k][l]-(i==0 ? 0 : v[i-1][l])-(j==0 ? 0 : v[k][j-1])+(i>0&&j>0 ? v[i-1][j-1] : 0);
    };
    return 0;
}