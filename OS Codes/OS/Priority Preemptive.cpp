#include <iostream>
using namespace std;

class Process {
    public:
        int arrivaltime;
        int bursttime;
        int remainingtime;
        int completiontime;
        int turnaroundtime;
        int waitingtime;
        int priority;
        bool completed;

        Process():arrivaltime(0),bursttime(0),remainingtime(0),completiontime(0),turnaroundtime(0),waitingtime(0),priority(0),completed(false){}

        void setdata(int at, int bt, int pr){
            arrivaltime=at;
            bursttime=bt;
            remainingtime=bt;
            priority=pr;
        }

        static void preemptivePriorityScheduling(Process* p, int size){
            int current=0;
            int completed=0;

            while(completed<size){
                int idx=-1;
                bool found=false;

                for(int i=0;i<size;i++){
                    if(p[i].arrivaltime<=current && !p[i].completed){
                        if(!found || p[i].priority<p[idx].priority){
                            idx=i;
                            found=true;
                        }
                    }
                }
                //idx contains least priority index
                if(found){
                    p[idx].remainingtime--;
                    current++;
                    if(p[idx].remainingtime==0){
                        p[idx].completed=true;
                        p[idx].completiontime=current;
                        p[idx].turnaroundtime=p[idx].completiontime-p[idx].arrivaltime;
                        p[idx].waitingtime=p[idx].turnaroundtime-p[idx].bursttime;
                        completed++;
                    }
                }
                else{
                    current++;
                }
            }
        }

        static void display(Process* p, int size){
            cout<<"Arrival\tBurst\tPriority\tComplete\tTurnAround\tWait"<<endl;
            for(int i=0;i<size;i++){
                cout<<p[i].arrivaltime<<"\t"<<p[i].bursttime<<"\t"<<p[i].priority<<"\t\t"<<p[i].completiontime<<"\t\t"<<p[i].turnaroundtime<<"\t\t"<<p[i].waitingtime<<endl;
            }
        }
};

int main(){
    int noprocess;
    cout<<"Enter Number Of Process: ";
    cin>>noprocess;
    Process* processes=new Process[noprocess];
    int at, bt, pr;
    for(int i=0;i<noprocess;i++){
        cout<<"Arrival Time: ";
        cin>>at;
        cout<<"Burst Time: ";
        cin>>bt;
        cout<<"Priority (lower number is higher priority): ";
        cin>>pr;
        processes[i].setdata(at,bt,pr);
    }

    Process::preemptivePriorityScheduling(processes,noprocess);
    Process::display(processes,noprocess);

    delete[] processes;
    return 0;
}