#include<bits/stdc++.h>
using namespace std;

struct Result {
    vector<int> ct, wt, tat, rt;
    int contextSwitches;
    double avgWT, avgTAT, avgRT, energyUsed;
};

Result round_robin(vector<int> at, vector<int> bt, int n, int tq, bool modified){

    vector<int> rem = bt;
    vector<int> ct(n), rt(n, -1), tat(n), wt(n);
    vector<bool> inq(n, false);

    queue<int> q;
    int time = *min_element(at.begin(), at.end());
    int totalBurst = accumulate(bt.begin(), bt.end(), 0);
    int contextSwitches = 0;

    double energy = 0;

    for(int i=0;i<n;i++){
        if(at[i] == time){
            q.push(i);
            inq[i] = true;
        }
    }

    while(!q.empty()){

        int exec = q.front();
        q.pop();
        inq[exec] = false;

        contextSwitches++;

        int currentQuantum = tq;
        double power = 8; 

        if(modified){
            int qs = q.size() + 1; 
            if(qs <= 2){
                currentQuantum = 4;
                power = 1;
            } else if(qs <= 4){
                currentQuantum = 3;
                power = 4;
            } else {
                currentQuantum = 2;
                power = 8;
            }
        }

        if(rt[exec] == -1) rt[exec] = time - at[exec];

        int run = min(currentQuantum, rem[exec]);
        rem[exec] -= run;
        time += run;

        energy += (power * run);

        for(int i=0;i<n;i++){
            if(at[i] <= time && rem[i] > 0 && !inq[i]){
                q.push(i);
                inq[i] = true;
            }
        }

        if(rem[exec] > 0){
            q.push(exec);
            inq[exec] = true;
        } else {
            ct[exec] = time;
        }
    }

    Result R;
    R.ct = ct;
    R.rt = rt;
    R.contextSwitches = contextSwitches;
    R.energyUsed = energy;

    double sumWT = 0, sumTAT = 0, sumRT = 0;
    for(int i=0;i<n;i++){
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        sumWT += wt[i];
        sumTAT += tat[i];
        sumRT += rt[i];
    }

    R.tat = tat;
    R.wt = wt;
    R.avgWT = sumWT/n;
    R.avgTAT = sumTAT/n;
    R.avgRT = sumRT/n;

    return R;
}



int main(){
    int n;
    cout<<"Enter number of processes: ";
    cin>>n;

    vector<int> at(n), bt(n);
    cout<<"Enter AT and BT for each process:\n";
    for(int i=0;i<n;i++){
        cout<<"P"<<i+1<<": ";
        cin>>at[i]>>bt[i];
    }

    int tq;
    cout<<"Enter time quantum for normal RR: ";
    cin>>tq;

    Result normalRR = round_robin(at, bt, n, tq, false);
    Result energyRR = round_robin(at, bt, n, tq, true);

    printResult(normalRR, at, bt, "Standard Round Robin");
    printResult(energyRR, at, bt, "Energy Efficient Round Robin");

    cout << "\n===== Comparison =====\n";
    cout << "Energy saved: " << normalRR.energyUsed - energyRR.energyUsed << endl;

    return 0;
}
