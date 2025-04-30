#include<iostream>
using namespace std;

void prt(int m){
    if(m <= 1) cout << 1;
    else cout << m << " * ";
    return;
}

int M(int m){
    prt(m);
    if(m <= 1) return 1;
    return m * M(m - 1);
}

int main(){
    int n;
    while(cin >> n){
        cout << n << "! = ";
        int ans = M(n);
        cout << " = " << ans << "\n";
    }
}