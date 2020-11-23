#include<iostream>
#include<cmath>
#include<complex>
#include<vector>
using namespace std;

const double PI = acos(0.0)*2;

vector<complex<double>> fft(vector<complex<double>> a, bool inverse=false){
    int n = a.size();
    int h = 0;
    while(1<<h < n) h++;
    for(int i = 0; i < n; i++){
        int j = 0;
        for(int k = 0; k < h; k++)  j |= (i>>k & 1) << (h-1-k);
        if(i < j)   swap(a[i], a[j]);
    }
    // butter-fly
    for(int b = 1; b < n; b *= 2){  // ステップb、ブロックサイズ2*b
        for(int j = 0; j < b; j++){ // ブロック内j個目
            complex<double> w = polar(1.0, -(2*PI) / (2*b) * j * (inverse ? -1 : 1));
            for(int k = 0; k < n; k += 2*b){    // kを先頭とするブロック
                complex<double> s = a[j+k];
                complex<double> t = a[j+k+b]*w;
                a[j+k] = s+t;
                a[j+k+b] = s-t;
            }
        }
    }
    if(inverse) for(int i = 0; i < n; i++)  a[i] /= n;
    return a;
}

vector<complex<double>> fft(vector<double> a, bool inverse=false){
    vector<complex<double>> a_complex(a.size());
    for(int i = 0; i < a.size(); i++)   a_complex[i] = complex<double>(a[i], 0);
    return fft(a_complex, inverse);
}

vector<double> convolve(vector<double> a, vector<double> b){
    int s = a.size() + b.size() - 1;
    int t = 1;
    while(t < s)    t *= 2;
    a.resize(t);
    b.resize(t);
    vector<complex<double>> A = fft(a);
    vector<complex<double>> B = fft(b);
    for(int i = 0; i < t; i++)  A[i] *= B[i];
    A = fft(A, true);
    a.resize(s);
    for(int i = 0; i < s; i++)  a[i] = A[i].real();
    return a;
}

int main(){
    int n;
    cin >> n;
    vector<double> a(n+1, 0), b(n+1, 0);
    for(int i = 1; i <= n; i++){
        cin >> a[i] >> b[i];
    }
    vector<double> ret = convolve(a, b);
    for(int i = 1; i < ret.size(); i++){
        cout << (int)(ret[i]+0.5) << endl;
    }
    return 0;
}
