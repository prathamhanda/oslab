#include <iostream>
using namespace std;
class fcfs{
    private:
        int arrivaltime;
        int bursttime;
        int completiontime;
        int turnaroundtime;
        int waitingtime;
    public:
        fcfs():arrivaltime(0),bursttime(0),completiontime(0),turnaroundtime(0),waitingtime(0){}
        void setdata(int at, int bt){
            arrivaltime=at;
            bursttime=bt;
        }
        void sortfcfs(fcfs *f,int size){
            for(int i=0;i<size-1;i++) {
                for(int j=0;j<size-i-1;j++){
                    if(f[j].arrivaltime>f[j+1].arrivaltime){
                        swap(f[j],f[j+1]);
                    }
                }
            }
        }
        
        void calctime(fcfs *f,int size){
            int current=0;
            for(int i=0;i<size;i++){
            	if(current<f->arrivaltime){
            		current=f->arrivaltime;
				}
                int backburst=f->bursttime;
                while(backburst!=0){
                    current++;
                    backburst--;
                }
                f->completiontime=current;
                f->turnaroundtime=f->completiontime-f->arrivaltime;
                f->waitingtime=f->turnaroundtime-f->bursttime;
                f++;
            }
        }
        void display(fcfs *f,int size){
            cout<<"Arrival\t\tBurst\t\tComplete\t\tTurnAround\t\tWait"<<endl;
            for(int i=0;i<size;i++){
                cout<<f->arrivaltime<<"\t\t"<<f->bursttime<<"\t\t"<<f->completiontime<<"\t\t\t"<<f->turnaroundtime<<"\t\t\t"<<f->waitingtime<<"\t\t\t"<<endl;
                f++;
            }
        }
};
int main(){
    int noprocess;
    cout<<"Enter Number Of Process: ";
    cin>>noprocess;
    fcfs *fcfsqueue=new fcfs[noprocess];
    fcfs *fcfstemp=fcfsqueue;
    int at,bt;
    for(int i=0;i<noprocess;i++){
        cout<<"Arrival Time: ";
        cin>>at;
        cout<<"Burst Time: ";
        cin>>bt;
        fcfstemp->setdata(at,bt);
        fcfstemp++;
    }
    fcfstemp=fcfsqueue;
    fcfs fback;
    fback.sortfcfs(fcfstemp,noprocess);
    fback.calctime(fcfstemp,noprocess);
    fback.display(fcfstemp,noprocess);
    return 0;
}