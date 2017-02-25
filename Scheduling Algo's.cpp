#include<iostream>
#include<vector>
#include<stdlib.h>
#include<time.h>
#include<stdio.h>
#include<graphics.h>
#define min(a,b) ((a)>(b)?(b):(a))
using namespace std;


int gd = DETECT, gm, x, y, color, angle = 0;


struct process{
int id;
int burst_time;
int arrival_time;
int turnaround_time;
int executed_time;
//int execution_time;
int waiting_time;
    process(){
        burst_time = 0;
        arrival_time = 0;
        turnaround_time = 0;
       // execution_time = 0;
        executed_time = 0;
        waiting_time = 0;
    }
};

struct execution{
int start_time;
int end_time;
int id;
};

vector<process> processes;
vector<execution> ready;
int takeInput(int index){

cout<<"Input Mode?\n0.Random\n1.Manually";
int ch;
int n;
int x = -1;
process temp;
cin>>ch;
switch(ch){
case 1:
cout<<"Enter Number of Processes\n";
cin>>n;
for(int i=0;i<n;i++){
     cout<<"Enter Arrival time and Burst time for process P["<<i+1<<"] ";
     temp.id = i+1;
     cin>>temp.arrival_time;
    cin>>temp.burst_time;
     processes.push_back(temp);
}
if(index==3){
        /**x = time quantum*/
cout<<"Enter Time quantum..";
cin>>x;
}
break;
case 0:
     srand(time(0));
     n = rand()%(6-4)+3+1;
     for(int i=0;i<n;i++){
     temp.id = i+1;
     temp.arrival_time = rand()%(15-0) + 0 + 1;
     temp.burst_time = rand()%(20-1) + 0 + 1;
     x = rand()%(5-0)+0+5;
         //cout<<temp.burst_time<<"\tP["<<temp.id<<"]\t"<<temp.arrival_time<<endl;
     processes.push_back(temp);
}
    break;
default:
    "Invalid Choice....";
    exit(0);
}
cout<<endl<<endl;
return x;
}

void sortArrival(){
    for(int i=0;i<processes.size();i++){
        for(int j=0;j<processes.size()-i-1;j++){
            if(processes.at(j).arrival_time>processes.at(j+1).arrival_time)
                swap(processes.at(j),processes.at(j+1));
        }
    }
}

void emptyProcesses(){
while(processes.size()){
    processes.pop_back();
}
while(ready.size()){
    ready.pop_back();
}
}


void displayResult(float avgw,float avgt,int index,bool preemptive,int tq){

char buff[10];
int i;
setcolor(0);
 /**Sort according to insertion time*/
for(i=0;i<processes.size()-1;i++){
    for(int j=0;j<processes.size()-i-1;j++){
        if(processes.at(j).id>processes.at(j+1).id)
            swap(processes.at(j),processes.at(j+1));
    }
}
    settextstyle(8,0,4);
    switch(index){
case 1:
    outtextxy(540,10,"First Come First Serve");
    break;
case 2:
    outtextxy(580,10,"Shortest Job First");
    if(preemptive)
        outtextxy(620,40,"(Preemptive)");
    else
         outtextxy(600,40,"(Non Preemptive)");
    break;
case 3:

    outtextxy(600,10,"Round Robin");
     outtextxy(580,40,"Time quantum = ");
      outtextxy(850,40,itoa(tq,buff,10));
    break;

    }
settextstyle(8,0,3);
outtextxy(80,100,"    Process        Arrival time        Burst time        Waiting time        Turnaround time");
settextstyle(8,0,1);
for(i=0;i<processes.size();i++){
        process p = processes.at(i);
    outtextxy(150,150+i*30,"P[ ");
    outtextxy(150+30,150+i*30,itoa(p.id,buff,10));
    outtextxy(190,150+i*30," ]");
    outtextxy(180+225,150+i*30,itoa(p.arrival_time,buff,10));
    outtextxy(180+500,150+i*30,itoa(p.burst_time,buff,10));
    outtextxy(180+755,150+i*30,itoa(p.waiting_time,buff,10));
    outtextxy(180+1080,150+i*30,itoa(p.turnaround_time,buff,10));
}
outtextxy(250,150+i*30+30,"Average Waiting time = ");
sprintf (buff, "%0.2f", avgw/processes.size());
outtextxy(520,150+i*30+30,buff);
outtextxy(250,150+i*30+60,"Average Turnaround time = ");
sprintf (buff, "%0.2f", avgt/processes.size());
outtextxy(550,150+i*30+60,buff);
getch();
closegraph();
}

void drawGantt(){
initgraph(&gd,&gm,"C:\\TurboC3\\BGI");
     delay(1000);
     setfillstyle(1,15);
     floodfill(getmaxx()/2,getmaxy()/2,15);
   char buff[10];
   int xx = 80;
   execution e;
   settextstyle(6,0,2);
   for(int i=0;i<ready.size();i++){
        e = ready.at(i);
        setfillstyle(1,e.id);
        setbkcolor(e.id);
        setcolor(0);
        setlinestyle(0,1,2);
        rectangle(xx,600,xx+(e.end_time-e.start_time)*20,700);
        floodfill(xx+10*(e.end_time-e.start_time),670,0);
        setlinestyle(0,1,1);
        setcolor(15);
        outtextxy(xx+10*(e.end_time-e.start_time)-5,630,itoa(e.id,buff,10));
        setbkcolor(15);
        setcolor(0);
         if(e.end_time-e.start_time<4)
            outtextxy(xx-10,570,itoa(e.start_time,buff,10));
        else
            outtextxy(xx-10,720,itoa(e.start_time,buff,10));


        xx += (e.end_time-e.start_time)*20;

            if(ready.at(i).end_time != ready.at((i+1)%ready.size()).start_time && i!=ready.size()-1){
                outtextxy(xx-10,570,itoa(e.end_time,buff,10));
                xx+=(ready.at((i+1)%ready.size()).start_time-ready.at(i).end_time)*10;
            }
            if(i==ready.size()-1){
                outtextxy(xx-10,720,itoa(e.end_time,buff,10));
            }

   }

}

void startFCFS(){
emptyProcesses();
int elapsed_time=0;
takeInput(1);
sortArrival();
float avgw=0,avgt=0;
/**Execution*/
for(int i=0;i<processes.size();i++){
        if(processes.at(i).arrival_time>elapsed_time)
            elapsed_time = processes.at(i).arrival_time;
    execution tem;
    tem.start_time = elapsed_time;
    tem.id = processes.at(i).id;
    //processes.at(i).execution_time = elapsed_time;
    processes.at(i).waiting_time = elapsed_time - processes.at(i).arrival_time;
    avgw+=processes.at(i).waiting_time;
    elapsed_time +=processes.at(i).burst_time;
    tem.end_time = elapsed_time;
    ready.push_back(tem);
    processes.at(i).turnaround_time = processes.at(i).waiting_time + processes.at(i).burst_time;
    avgt+=processes.at(i).turnaround_time;
}
/**Display result*/
drawGantt();
displayResult(avgw,avgt,1,false,-1);
}
void startSJF(){
emptyProcesses();
bool preemptive;
int elapsed_time=0;
int ch;
 float avgw=0,avgt=0;
takeInput(2);
cout<<"1.Preemptive 2.Non preemptive\n";
cin>>ch;
switch(ch){
case 1:
    preemptive = true;
    break;
case 2:
    preemptive = false;
    break;
default:
    cout<<"Invalid Choice";
    exit(0);
}
sortArrival();
if(!preemptive){

      sortArrival();
      int jump = 0;
    vector<process*> readyQueue;
    while(1){
      for(int i=0;i<processes.size();i++){
        if(processes.at(i).arrival_time<=elapsed_time && processes.at(i).executed_time==0)
           readyQueue.push_back(&processes.at(i));
        else if(processes.at(i).arrival_time>elapsed_time){
                if(jump==0)
                    jump = processes.at(i).arrival_time;
                    break;
        }
      }
        if(jump==0 && readyQueue.size()==0)
                break;
        else if(readyQueue.size()==0){
            elapsed_time = jump;
            jump = 0;
            continue;
        }
     /**Sort according to burst time*/
    for(int i=0;i<readyQueue.size();i++){
        for(int j=0;j<readyQueue.size()-i-1;j++){
            if(readyQueue.at(j)->burst_time>readyQueue.at(j+1)->burst_time)
                swap(readyQueue.at(j),readyQueue.at(j+1));
        }
    }
        for(int i=0;i<=0;i++){
             execution tem;
            tem.start_time = elapsed_time;
      //      readyQueue.at(i)->execution_time = elapsed_time;
            tem.id = readyQueue.at(i)->id;
            elapsed_time+=readyQueue.at(i)->burst_time;
            readyQueue.at(i)->executed_time = readyQueue.at(i)->burst_time;
            readyQueue.at(i)->turnaround_time = elapsed_time - readyQueue.at(i)->arrival_time;

   readyQueue.at(i)->waiting_time = readyQueue.at(i)->turnaround_time - readyQueue.at(i)->burst_time ;
    avgw+=readyQueue.at(i)->waiting_time;
    tem.end_time = elapsed_time;
    ready.push_back(tem);
    avgt+=readyQueue.at(i)->turnaround_time;
        }
        while(readyQueue.size())
            readyQueue.pop_back();
    }

}
if(preemptive){
avgt = 0;
avgw = 0;
      int jump = 0,k,next_arrival;
      elapsed_time = 0;
    vector<process*> readyQueue;
    //displayResult(0,0);
    int limit = processes.at(processes.size()-1).arrival_time;
    while(1){
      for(int i=0;i<processes.size()&& elapsed_time<=limit;i++){
            if(processes.at(i).executed_time == processes.at(i).burst_time)
                continue;
        if(processes.at(i).arrival_time<=elapsed_time && processes.at(i).executed_time!= processes.at(i).burst_time){
           readyQueue.push_back(&processes.at(i));
           for(k=0;k<processes.size();k++)
            if(processes.at(k).arrival_time>elapsed_time)
                break;
           if(k!=processes.size())
            next_arrival = processes.at(k).arrival_time;
            else{
                next_arrival = 9999;
            }
        }
        else if(processes.at(i).arrival_time>elapsed_time){
                if(jump==0)
                    jump = processes.at(i).arrival_time;
                    break;
        }
      }
      if(elapsed_time<=limit){
        if(jump==0 && readyQueue.size()==0)
                break;
        else if(readyQueue.size()==0){
            elapsed_time = jump;
            jump = 0;
            continue;
        }
      }

       if(elapsed_time>limit){
       for(int i=0;i<processes.size();i++){
            if(processes.at(i).executed_time != processes.at(i).burst_time)
                readyQueue.push_back(&processes.at(i));
       }
        if(readyQueue.size()==0)
            break;
      }

     /**Sort according to burst time*/
    for(int i=0;i<readyQueue.size();i++){
        for(int j=0;j<readyQueue.size()-i-1;j++){
            if(readyQueue.at(j)->burst_time-readyQueue.at(j)->executed_time>
               readyQueue.at(j+1)->burst_time-readyQueue.at(j+1)->executed_time)
                swap(readyQueue.at(j),readyQueue.at(j+1));
        }
    }
    int min = 0;

    execution tem;
    tem.start_time = elapsed_time;
    tem.id = readyQueue.at(min)->id;
    if(readyQueue.at(min)->burst_time-readyQueue.at(min)->executed_time>next_arrival-elapsed_time){
        tem.end_time = next_arrival;
        elapsed_time+=tem.end_time - tem.start_time;
        readyQueue.at(min)->executed_time +=tem.end_time - tem.start_time;
         if(ready.size()!=0 && ready.at(ready.size()-1).id == tem.id)
            ready.at(ready.size()-1).end_time = tem.end_time;
        else
        ready.push_back(tem);
    }else{
     tem.end_time = readyQueue.at(min)->burst_time-readyQueue.at(min)->executed_time + elapsed_time;
      elapsed_time+=tem.end_time - tem.start_time;
     //readyQueue.at(min)->turnaround_time = elapsed_time - readyQueue.at(min)->arrival_time;
      //readyQueue.at(0)->waiting_time = elapsed_time - readyQueue.at(0)->arrival_time - readyQueue.at(0)->burst_time ;
        readyQueue.at(min)->executed_time +=tem.end_time - tem.start_time;
        if(ready.size()!=0 && ready.at(ready.size()-1).id == tem.id)
            ready.at(ready.size()-1).end_time = tem.end_time;
        else
        ready.push_back(tem);
    }
   if(readyQueue.at(min)->executed_time == readyQueue.at(min)->burst_time){
       readyQueue.at(min)->turnaround_time = elapsed_time - readyQueue.at(min)->arrival_time;
       avgt+=readyQueue.at(min)->turnaround_time;
        readyQueue.at(min)->waiting_time = elapsed_time - readyQueue.at(min)->arrival_time - readyQueue.at(min)->burst_time;
         avgw+=readyQueue.at(min)->waiting_time;
    }
    while(readyQueue.size())
        readyQueue.pop_back();

    }

}
drawGantt();
displayResult(avgw,avgt,2,preemptive,-1);
}
void startRR(){
emptyProcesses();
int tq;
int elapsed_time=0;
tq = takeInput(3);
//vector<process> readyQueue = processes;
/**Execution*/
sortArrival();
 //cout<<"Process\tBurst time\tExecution time\n";
 vector<process*> readyQueue;

 int br=-1;
while(1){
    bool taskCompleted = true;
    int jump = 0;
    for(int i=0;i<processes.size();i++){
            //cout<<"check"<<processes.at(i).id<<endl;
             if(processes.at(i).executed_time == processes.at(i).burst_time){
                continue;
             }
             else if(processes.at(i).arrival_time<=elapsed_time && processes.at(i).executed_time==0){
              //      cout<<"New"<<processes.at(i).id<<endl;
                    readyQueue.push_back(&processes.at(i));
                    taskCompleted = false;
             }
             else{
                    if(jump == 0)
                        jump = processes.at(i).arrival_time;
                taskCompleted = false;
                //break;
             }
    }

    for(int i=0;i<processes.size();i++){
             if(processes.at(i).executed_time == processes.at(i).burst_time ){
                continue;
             }
             else if(processes.at(i).arrival_time<=elapsed_time && processes.at(i).executed_time!=0){
                    readyQueue.push_back(&processes.at(i));
                    br = i;
                    taskCompleted = false;
             }
             else{
                    if(jump == 0)
                        jump = processes.at(i).arrival_time;
                taskCompleted = false;
                //break;
             }
    }
    if(readyQueue.size()==0 && taskCompleted)
        break;
    else if(readyQueue.size()==0){
        elapsed_time = jump;
        jump = 0;
        continue;
    }
//cout<<"ReadyQueue"<<readyQueue.size()<<endl;
    for(int i=0;i<readyQueue.size();i++){
    execution tem;
    tem.start_time = elapsed_time;
    tem.id = readyQueue.at(i)->id;
        elapsed_time +=min(readyQueue.at(i)->burst_time - readyQueue.at(i)->executed_time,tq);
        tem.end_time = elapsed_time;
        ready.push_back(tem);

        readyQueue.at(i)->executed_time+=min(readyQueue.at(i)->burst_time- readyQueue.at(i)->executed_time,tq);
        if(readyQueue.at(i)->burst_time == readyQueue.at(i)->executed_time)
            readyQueue.at(i)->turnaround_time = elapsed_time - readyQueue.at(i)->arrival_time;
    }
   // readyQueue.clear();
while(readyQueue.size())
    readyQueue.pop_back();
}
float avgw=0,avgt=0;
for(int i=0;i<processes.size();i++){
        avgt+= processes.at(i).turnaround_time;
    avgw += processes.at(i).turnaround_time - processes.at(i).burst_time;
    processes.at(i).waiting_time = processes.at(i).turnaround_time - processes.at(i).burst_time;
}
drawGantt();
displayResult(avgw,avgt,3,false,tq);

}



int main(){
     int ch;
    while(1){
        cout<<"1.FCFS\n2.SJF\n3.RR\n0.Exit";
    cin>>ch;
    switch(ch){
    case 0:
        return 0;
case 1:
    startFCFS();
    break;
case 2:
    startSJF();
    break;
case 3:
    startRR();
    break;
default:
    "Invalid Choice";
    }


    }
return 0;
}
