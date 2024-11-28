#include <bits/stdc++.h>
using namespace std;

class Process {
    private:
        int arrivaltime;
        int bursttime;
        int remainingtime;
        int completiontime;
        int turnaroundtime;
        int waitingtime;
        bool completed;
    public:
        Process():arrivaltime(0),bursttime(0),remainingtime(0),completiontime(0),turnaroundtime(0),waitingtime(0),completed(false){}
        void setdata(int at, int bt){
            arrivaltime=at;
            bursttime=bt;
            remainingtime=bt;
        }

        static void calculateSRTF(Process* processes, int size){
            int current=0;
            int completed=0; //Counts the number of processes that have completed execution.

            while(completed<size){
                int idx=-1; //to indicate that no valid process has been selected yet.
                bool found=false; //determine if a valid process is found with the shortest remaining time.

                //The loop iterates over all processes to find the one with the shortest remaining time that has arrived and is not yet completed.
                for(int i=0;i<size;i++){
                    if(processes[i].arrivaltime<=current && !processes[i].completed){
                        if(!found || processes[i].remainingtime<processes[idx].remainingtime){
                            idx=i; //This marks the current process as the one with the shortest remaining time found so far.
                            found=true; //indicating that a valid process has been found in this iteration.
                        }
                    }
                }
                
                if(found){
                    processes[idx].remainingtime--;
                    current++;

                    if(processes[idx].remainingtime==0){
                        processes[idx].completed=true;
                        processes[idx].completiontime=current;
                        processes[idx].turnaroundtime=processes[idx].completiontime-processes[idx].arrivaltime;
                        processes[idx].waitingtime=processes[idx].turnaroundtime-processes[idx].bursttime;
                        completed++;
                    }
                }
                else{  //If no valid process is found, simply increment current to simulate the passage of time.
                    current++;
                }
            }
        }

        static void display(Process* processes, int size){
            cout<<"Arrival\t\tBurst\t\tComplete\t\tTurnAround\t\tWait"<<endl;
            for(int i=0;i<size;i++){
                cout<<processes->arrivaltime<<"\t\t"<<processes->bursttime<<"\t\t"<<processes->completiontime<<"\t\t\t"<<processes->turnaroundtime<<"\t\t\t"<<processes->waitingtime<<"\t\t\t"<<endl;
                processes++;
            }
        }
};

int main(){
    int noprocess;
    cout<<"Enter Number Of Process: ";
    cin>>noprocess;
    Process* processes=new Process[noprocess];
    Process* processestemp=processes;
    int at, bt;
    for(int i=0;i<noprocess;i++){
        cout<<"Arrival Time: ";
        cin>>at;
        cout<<"Burst Time: ";
        cin>>bt;
        processestemp->setdata(at,bt);
        processestemp++;
    }
    processestemp=processes;
    Process back;
    back.calculateSRTF(processestemp,noprocess);
    back.display(processestemp,noprocess);
    return 0;
}