#include<bits/stdc++.h>
using namespace std;
int round_robin(vector<int>at, vector<int> bt){
    int min=*min_element(at.begin(),at.end());
    return min;
}
int main(){
    int n;
    cout<<"Enter number of processes: ";
    cin>>n;
    cout<<endl;
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
    cout<<endl;
    int time_quantum;
    cout<<"Enter time quantum: ";
    cin>>time_quantum;
    cout<<endl<<"======Standard Round Robin====="<<endl;
    cout<<round_robin(at,bt);
}
