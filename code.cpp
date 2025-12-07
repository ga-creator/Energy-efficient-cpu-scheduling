#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cout<<"Enter number of processes: ";
    cin>>n;
    vector<int>at;
    vector<int>bt;
    int count=1;
    while(n--){
        int a,b;
        cout<<"P"<<count<<" ";
        cin>>a>>b;
        at.push_back(a);
        bt.push_back(b);
        count++;
    }
}
