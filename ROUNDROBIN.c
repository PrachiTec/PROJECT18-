#include<stdio.h>
#include<conio.h>
struct ProcessHeader
{
char Process_Name;
int turnaround_time;
int store_burst_time;
int arrival_time;
int burst_time;
int waiting_time;
int finished;
}ph[20];
int process_queue[20];
int num;
int queue_front=-1,queue_rear=-1;

int process_dequeue()
{
if(queue_front==-1)
printf("underflow");
int queue_data=process_queue[queue_front];
if(queue_front==queue_rear)
queue_front=queue_rear=-1;
else
queue_front++;
return queue_data;
}

void process_enqueue(int i)
{
if(queue_rear==20)
printf("overflow");
queue_rear++;
process_queue[queue_rear]=i;
if(queue_front==-1)
queue_front=0;
}

void sorting_process()
{
struct ProcessHeader queue_data;
int j,i;
for(j=0;j<num-1;j++)
for(i=j+1;i<num;i++)
{
if(ph[j].arrival_time>ph[i].arrival_time)
{
queue_data=ph[j];
ph[j]=ph[i];
ph[i]=queue_data;
}
}
}

int available_in_queue(int i)
{
int j;
for(j=queue_front;j<=queue_rear;j++)
{
if(process_queue[j]==i)
return 1;
}
return 0;
}

//*****************************************MAIN FUNCTION**********************************************************************

int main()
{
float average_waiting_time=0,average_turnaround_time=0;
int time_quanta;
int i,j;
int timing=0;
int sum_of_burst_time=0;
char ch;

printf("*************************Scheduling_of_processes:*******************************\n");

 printf("\nEnter number of process:");
 scanf("%d",&num);
 for(ch='a',i=0;i<num;ch++,i++)
 {
 ph[i].Process_Name=ch;
 printf("\n\t***********************  PROCESS  %c  UNDERCONSIDERATION *************************: ",ph[i].Process_Name);
 printf("\n enter process Arrival Time:");
 scanf("%d",&ph[i].arrival_time);
 printf("\nenter process Burst Time:");
 scanf("%d",&ph[i].burst_time);
 ph[i].store_burst_time=ph[i].burst_time;
 sum_of_burst_time+=ph[i].burst_time;
 ph[i].finished=0;

 }
printf("\n enter The Time_quanta:");
scanf("%d",&time_quanta);


printf("\t\t\ norder of process execution: ");
sorting_process();
process_enqueue(0);
for(timing=ph[0].arrival_time;timing<sum_of_burst_time;)
{
i=process_dequeue();

if(ph[i].store_burst_time<=time_quanta)
{
timing+=ph[i].store_burst_time;
ph[i].store_burst_time=0;
ph[i].finished=1;
    printf(" %c ",ph[i].Process_Name);
            ph[i].waiting_time=timing-ph[i].arrival_time-ph[i].burst_time;
            ph[i].turnaround_time=timing-ph[i].arrival_time;
            for(j=0;j<num;j++)
            {
            if( ph[j].finished!=1&& available_in_queue(j)!=1 && ph[j].arrival_time<=timing )
            {
            process_enqueue(j);
            }
            }
            }
    else
    {
    timing+=time_quanta;
    ph[i].store_burst_time-=time_quanta;
    printf(" %c ",ph[i].Process_Name);
    for(j=0;j<num;j++)
            {
            if(  ph[j].finished!=1&&i!=j&& available_in_queue(j)!=1 && ph[j].arrival_time<=timing)
             {
            process_enqueue(j);

            }
           }
           process_enqueue(i);

    }



}

printf("\n\n process\t    Arrival_time\tBurst_time\tWaiting_time\tTurnaround_time");
for(i=0;i<num;i++)
{average_waiting_time+=ph[i].waiting_time;
 average_turnaround_time+=ph[i].turnaround_time;
printf("\n%c\t%d\t%d\t%d\t%d",ph[i].Process_Name,ph[i].arrival_time,ph[i].burst_time,ph[i].waiting_time,ph[i].turnaround_time);
}
printf("\naverage waiting time of process:%f",average_waiting_time/num);
printf("\naverage turnaround time of process:%f",average_turnaround_time/num);
getch();
return 0;
}
