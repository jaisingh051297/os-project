/*
 schedules N  processes which arrive at different time intervals and each process is allocated the CPU for 
 a specific user input time unit, processes are scheduled using a preemptive round robin scheduling algorithm. 
 Each process must be assigned a numerical priority, with a higher number indicating a higher relative priority. 
 In addition to the processes one task has priority 0. The length of a time quantum is T units, where T is the 
 custom time considered as time quantum for processing. If a process is preempted by a higher priority process, 
 the preempted process is placed at the end of the queue. Design a scheduler so that the task with priority 0 
 does not starve for resources and gets the CPU at some time unit to execute. Also compute waiting time, turn 
 around.
*/
 
#include<stdio.h>
#include<iostream>
#include<queue>

using namespace std;

#define MAX 1000
#define QUANTA 4

int flag[MAX],at[MAX],bt[MAX],pt[MAX],rt[MAX];
int ft[MAX],fe[MAX],fe_flag[MAX],pid[MAX],tms,qt[MAX];


queue<int> q;  

void RoundRobin()
{
      if(!q.empty())
      {
      	if(rt[q.front()]>0 && qt[q.front()]<4)
      	{
          		qt[q.front()]++;
          		rt[q.front()]--;
          		if(rt[q.front()]==0)
          		{
            	ft[q.front()]=tms+1;
            	q.pop();
          		}
          		if(rt[q.front()]!=0 && qt[q.front()]==4)
          		{
				qt[q.front()]=0;
				q.push(q.front());
				q.pop();
          		}
        	}
      }
}

int main()
{double avgwait;
    int i=0,n=0,smallest=0,last_smallest=-1,min,sum=0,large=0,calwait=0;
    printf("\n\n\n\nenter no of processes  :  ");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {printf("enter pid , arrivaltime, burstime, priority  ");
    		scanf("%d %d %d %d",&pid[i],&at[i],&bt[i],&pt[i]);
    		if(at[i]>large)
    		  	large=at[i];
    		  sum+=bt[i];
    		  rt[i]=bt[i];
    }
    min=MAX;
    for(tms=0;!q.empty() || tms<=sum+large ;tms++)
    {
      min=MAX;
      smallest=-1;
      for(i=0;i<n;i++)
      {
      	if(at[i]<=tms && pt[i]<min && rt[i]>0 && !flag[i])
      	{
      		min=pt[i];
          		smallest=i;
        	}
      }
      if(smallest==-1 && !q.empty())
      {
      	if(last_smallest !=-1 && rt[last_smallest]==0)
      	{
      		ft[last_smallest]=tms;
          		flag[last_smallest]=1;
        	}
        	last_smallest=-1;
        	RoundRobin();
        	continue;
      }
      else if(smallest!=-1 && !q.empty() && last_smallest==-1)
      {
      	if(qt[q.front()]<=4 && qt[q.front()]>0)
      	{
      		q.push(q.front());
      		q.pop();
        	}
      }
      if(smallest!=-1 && !fe_flag[smallest])
      {
      	fe[smallest]=tms-at[smallest];
      	fe_flag[smallest]=1;
      }
      if( smallest!=last_smallest && last_smallest!=-1 && !flag[last_smallest])
      {
      	q.push(last_smallest);
      	flag[last_smallest]=1;
      }
      if(smallest !=-1)
      	rt[smallest]--;
      
      if((smallest !=-1) && ((rt[smallest]==0) ||(bt[smallest]-rt[smallest])==QUANTA))
      {
      	if((bt[smallest]-rt[smallest])==QUANTA && rt[smallest]!=0)
      	{
      		flag[smallest]=1;
      		q.push(smallest);
        	}
       	else if(smallest!=-1)
       	{
          		ft[smallest]=tms+1;
          		flag[smallest]=1;
        	}
      }
      last_smallest=smallest;
    }
    	   printf("process id :   Response time :  finish time :   waiting time :\n");
   for(int i=0;i<n;i++){
 calwait=ft[i]-bt[i]-at[i];
	   avgwait=avgwait+calwait;

	   printf("        %d  :\t\t  %d  :\t\t %d  :\t\t  %d  :\n",pid[i],fe[i],ft[i],ft[i]-bt[i]-at[i]);
	 
    }
 avgwait=avgwait/n;
 printf("average waiting time :   %f\n",avgwait);
    return 0;
}
