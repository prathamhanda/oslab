#include <bits/stdc++.h>
using namespace std;
class rr{
    private:
        int arrivaltime;
        int bursttime;
        int completiontime;
        int turnaroundtime;
        int waitingtime;
        int remainingtime;
    public:
        rr():arrivaltime(0),bursttime(0),completiontime(0),turnaroundtime(0),waitingtime(0),remainingtime(0){}
        void setdata(int at, int bt){
            arrivaltime=at;
            bursttime=bt;
            remainingtime=bt;
        }
        static void sortr(rr *r,int size){
            for(int i=0;i<size-1;i++) {
                for(int j=0;j<size-i-1;j++){
                    if(r[j].arrivaltime>r[j+1].arrivaltime){
                        swap(r[j],r[j+1]);
                    }
                }
            }
        }
        static void roundrobin(rr *r,int size, int tq){
            int current=0;
            bool temp;
            while(true){
                temp=false;
                for(int i=0;i<size;i++){
                    if(r[i].remainingtime>0 && r[i].arrivaltime<=current){
                        temp=true;
                        if(r[i].remainingtime>tq){
                            current=current+tq;
                            r[i].remainingtime=r[i].remainingtime-tq;
                        }
                        else{
                            current=current+r[i].remainingtime;
                            r[i].completiontime=current;
                            r[i].turnaroundtime=r[i].completiontime-r[i].arrivaltime;
                            r[i].waitingtime=r[i].turnaroundtime-r[i].bursttime;
                            r[i].remainingtime=0;
                        }
                    }
                }
                if(temp==false){
                    break;
                }
            }
        }
        static void display(rr *r,int size){
            cout<<"Arrival\t\tBurst\t\tComplete\t\tTurnAround\t\tWait"<<endl;
            for(int i=0;i<size;i++){
                cout<<r->arrivaltime<<"\t\t"<<r->bursttime<<"\t\t"<<r->completiontime<<"\t\t\t"<<r->turnaroundtime<<"\t\t\t"<<r->waitingtime<<"\t\t\t"<<endl;
                r++;
            }
        }
};
int main(){
    int noprocess;
    cout<<"Enter Number Of Process: ";
    cin>>noprocess;
    rr *rrqueue=new rr[noprocess];
    int at,bt,tq;
    cout<<"Enter Time Quantum: ";
    cin>>tq;
    for(int i=0;i<noprocess;i++){
        cout<<"Arrival Time: ";
        cin>>at;
        cout<<"Burst Time: ";
        cin>>bt;
        rrqueue[i].setdata(at,bt);
    }
    rr::sortr(rrqueue,noprocess);
    rr::roundrobin(rrqueue,noprocess,tq);
    rr::display(rrqueue,noprocess);
    return 0;
}