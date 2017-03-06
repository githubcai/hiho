#include <string>
#include <iostream>
using namespace std;

int main(){
    int n, m; cin >> n >> m;
    string str;
    if(n == m){
        for(int i = 0; i < n; ++i) str += "01";
    }else if(n < m){
        if(n == m - 1){
            str += "1";
            for(int i = 0; i < n; ++i) str += "01";
        }else{
            str = "NO";
        }
    }else{
        for(int i = 0; i < m; ++i) str += "01";
        for(int i = m; i < n; ++i) str += "0";
    }
    cout << str << endl;
    return 0;
}
