#include<iostream>
#include<cstring>
#include<vector>
using namespace std;

// strをdelで区切る.いずれdelがstringでも大丈夫なように作り変える.
vector<string> split(string str, char del){
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


int main(){
    cout << startsWith("0010","01") << endl;
    return 0;
}