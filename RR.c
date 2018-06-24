#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/dir.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
struct process {
int   process_id;
int start_time;
int end_time;
int arriv_time;
int cpu_time;
int no_tickets;
int remt;

};


#define MAX 1024

struct process intArray[MAX];
int front=0;
int rear = -1;
int itemCount = 0;


struct process peek() {
   return intArray[front];
}

bool isEmpty() {
   return itemCount == 0;
}

bool isFull() {
   return itemCount == MAX;
}

int size() {
   return itemCount;
}  

void insert(struct process data) {

   if(!isFull()) {
	
      if(rear == MAX-1) {
         rear = -1;            
      }       

      intArray[++rear] = data;
      itemCount++;
   }
}

struct process removeData() {
   struct process data = intArray[front++];
	
   if(front == MAX) {
      front = 0;
   }
	
   itemCount--;
   return data;  
}
void  RR(int quantum,int totaltime) {
FILE *f = fopen("outputRR.txt", "a");
if (f == NULL)
{
    printf("Error opening file!\n");
    exit(1);
}
    clock_t start;
start = clock(); //start time 
    int msec = 0 ;//counter of time
    int iterations =0; // fe km iteration 
    //totaltime=1000;
   int t=0; //total time
   float avgTR=0.0;
   int TR=0;
   int WT=0;
   float avgWT=0;
   int count=0;
 while (msec<totaltime && t<totaltime){
  if(quantum==msec || msec==peek().remt && quantum>msec ){
   // printf("test elarf dh %d \n" ,msec==peek().cpu_time && quantum>msec);
   struct process peekq;
   peekq=peek();
   t=t+msec;
     printf(" Time : %d " ,t-msec);
    fprintf(f," Time : %d " ,t-msec);
    printf("P%d Entering quantum \n" ,peekq.process_id);
     fprintf(f,"P%d Entering quantum \n" ,peekq.process_id);
      peekq.remt=peekq.remt-msec;
 
     if( peekq.remt>0){
       struct process test;
     test =removeData();
     test.remt=test.remt-msec;
    insert(test);
    }
    else{
       // printf("else cpu %d \n" , peekq.cpu_time);
       printf(" Time : %d " ,t);
       fprintf(f," Time : %d " ,t);
        peekq.end_time=t;
       printf("P%d leaving" ,peekq.process_id);
       fprintf(f,"P%d leaving" ,peekq.process_id);
        printf(" turnarount T: %d " ,peekq.end_time-peekq.arriv_time);
      fprintf(f," turnarount T: %d " ,peekq.end_time-peekq.arriv_time);
      TR=TR+peekq.end_time-peekq.arriv_time;
      WT=WT+(peekq.end_time-peekq.arriv_time)-peekq.cpu_time;
      printf("Waiting time: : %d \n" , (peekq.end_time-peekq.arriv_time)-peekq.cpu_time);
      fprintf(f,"Waiting time: : %d \n" , (peekq.end_time-peekq.arriv_time)-peekq.cpu_time);
      count++;
   // printf(" turnarount TR: %d , count:%d \n" ,TR,count);
       removeData();
      
      
       }
   msec=0;
   start = clock();
 }

  clock_t difference = clock() - start;
  msec = difference * 1000 / CLOCKS_PER_SEC;
  iterations++;
 }
avgTR=TR/count;
avgWT=WT/count;
printf("Avg Waiting Time =  %f \n",avgWT);
fprintf(f,"Avg Waiting Time =  %f \n",avgWT);
printf("Avg Turnaround Time =  %f \n",avgTR);
fprintf(f,"Avg Turnaround Time =  %f \n",avgTR);
printf("Time taken %d seconds %d milliseconds %d iterations\n",msec/1000, t, iterations);
fclose(f);
}






int main() {
   FILE * fp;
struct process pr[1024];
char line[256];
size_t len = 0;
ssize_t read;
int i =0;
char *pch;
int parsestoint;
char cpyph;
int totaltime =0;
struct process test;
    fp = fopen("/home/mohamed/Desktop/OS_MP2/OS_MP2/Input2.in", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
   fgets(line,256,fp);
   int quant= atoi(line);
   fgets(line,256,fp);
   int tickets = atoi(line);
 while(fgets(line,256,fp)){
   struct process p;
   //printf("%s \n",line);
   pch = strtok(line,",");
   sscanf( pch ,"%d",&parsestoint);
   p.process_id=parsestoint;
   pch = strtok(NULL,",");
   sscanf( pch ,"%d",&parsestoint);
    p.arriv_time=parsestoint;
    pch = strtok(NULL,",");
   sscanf( pch ,"%d",&parsestoint);
    p.cpu_time=parsestoint;
    p.remt= p.cpu_time;
    //pr[i]=p;
     insert(p);
    totaltime = totaltime+p.cpu_time;
   //test = removeData();
   // printf("%d \n",test.process_id);
  // printf("%d \n",*(dequeue(queue))); 
   //printf("%d \n",p.arriv_time);
    //printf("%d \n",p.process_id);
    //printf("%d \n",p.cpu_time);
    i++;
}

    RR(quant,totaltime);



    fclose(fp);
    exit(EXIT_SUCCESS);
}
