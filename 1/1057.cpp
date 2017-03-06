#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <map>
using namespace std;

struct Node{
    string name, time;
};

int tranTime(string time){
    int ret = 0;
    string temp = "";
    time += ":";
    for(int i = 0; i < time.size(); ++i){
        if(time[i] == ':'){
            stringstream ss(temp);
            int itemp;
            ss >> itemp;
            ret = ret * 60 + itemp;
            temp = "";
        }else{
            temp += time[i];
        }
    }
    return ret;
}

string cal(string st, string ed){
    int time, mod = 3600, ist = tranTime(st), ied = tranTime(ed);
    stringstream ss;
    time = ied - ist;
    if(time < 0) return "-1";
    while(mod > 0){
        int temp = time / mod;
        time %= mod;
        mod /= 60;
        if(temp < 10) ss << "0";
        ss << temp;
        if(mod > 0) ss << ":";
    }
    return ss.str();
}

int main(){
    int N; cin >> N;
    stack<Node> store;
    map<int, string> ref;
    map<string, string> result;
    string com;
    Node node;
    bool flag = true;
    int cnt = 1;
    for(int i = 0; i < N; ++i){
        cin >> node.name >> node.time >> com;
        if(flag){
            if(com == "START"){
                store.push(node);
                ref[cnt++] = node.name;
            }else{
                Node temp = store.top(); store.pop();
                if(temp.name != node.name){
                    flag = false;
                    continue;
                }
                temp.time = cal(temp.time, node.time);
                if(temp.time == "-1"){
                    flag = false;
                    continue;
                }
                result[temp.name] = temp.time;
            }
        }
    }
    if(!store.empty()) flag = false;
    if(flag){
        for(auto iter = ref.begin(); iter != ref.end(); ++iter){
            cout << iter->second << " " << result[iter->second] << endl;
        }
    }else{
        cout << "Incorrect performance log" << endl;
    }
    return 0;
}
