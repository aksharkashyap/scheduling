#include<stdio.h>
#include<limits.h>

//round robin
//1st iteration TQ=3
//2nd iteration TQ=6 (waiting processes)
//3rd iteration SJF (waiting processes)

int arrivalTime[50],burstTime[50],waitingTime[50],remainingBT[50],TurnAroundTime[50],compltnTime[50];
int time = 0; // Current time

int timeQauntum =3;int check=0,checkBT=0;
int pos;
int totalBT=0,completionTime;
int posMinBT = 0, processDone = 0, minimumBT = INT_MAX,TAT=0;


bool flag = false;

int n;

void calcWait();
void sjf();



//------main-----------------
int main(){

//enter the num of processes
printf("Please enter number of processes: ");
scanf("%d",&n);

// ask for arrival and burst time
for (int i=0;i<n;i++){
printf("Arrival Time for Process: %d\n",i+1);
scanf("%d",&arrivalTime[i]);

printf("Burst Time for Process: %d\n",i+1);
scanf("%d",&burstTime[i]);
printf("-------------------------------------------------\n");
}

for (int i = 0 ; i < n ; i++){ // Make a copy of burst times
        remainingBT[i] =  burstTime[i];
 }

calcWait();

if(checkBT>0){
timeQauntum=6;
calcWait();
}

if(checkBT>0){
    sjf();
}

checkBT=0;
for(int i=0;i<n;i++){
    checkBT += remainingBT[i];
}


//TAT calculation
for (int i=0; i<n; i++){
    TurnAroundTime[i] = burstTime[i] + waitingTime[i];
    compltnTime[i] = TurnAroundTime[i] + arrivalTime[i];
}

printf("Current Time %d\n",time);
printf("TotalRemainingBT %d\n",checkBT);
printf("ProcessNum ||  Arrival time ||  Burst time || Waiting Time || TurnaroundTime || completionTime ||remaining\n");

for (int i=0; i<n; i++){
   // printf("-----------------------------------------------------------------\n");
    printf("Process %d  || \t",i+1);
    printf("%d\t    || \t",arrivalTime[i] );
    printf("%d\t   || \t",burstTime[i] );
    printf("%d\t    || \t",waitingTime[i] );
    printf("%d\t    || \t",TurnAroundTime[i] );
    printf("%d\t    || \t",compltnTime[i] );
    printf("%d\t    || \n",remainingBT[i] );

  //  printf("-----------------------------------------------------------------\n");

}
}


void calcWait(){

    bool flag = false;

condnCheck:
    for(int i=0;i<n;i++){
        if(remainingBT[i]>timeQauntum && arrivalTime[i]<=time && remainingBT[i]>0){
            remainingBT[i] -= timeQauntum;
            time += timeQauntum;
            flag = true;

        }
        else if(remainingBT[i]<=timeQauntum && arrivalTime[i]<=time && remainingBT[i]>0){
           // while(remainingBT[i] !=0){
            //    time = time +1;
            //    remainingBT[i]--;}
            time = time + remainingBT[i];
            remainingBT[i] = 0;
            flag = true;
          }



        if(remainingBT[i] == 0){
            waitingTime[i] = time - arrivalTime[i] - burstTime[i];
            flag =true;
         }
        if(flag == false){
            time++;
            goto condnCheck;
        }


}

checkBT=0;
for(int i=0;i<n;i++){
    checkBT += remainingBT[i];
}
}

int smallestBT = INT_MAX;

void sjf(){

while (1)
 {
        flag = false;
        for (int i = 0; i < n; i++) {

            if (remainingBT[i] > 0 && (remainingBT[i] < minimumBT)){

                posMinBT = i;
                minimumBT = remainingBT[i];
                flag = true;
            }

        if (flag == false) {
            continue; // again iterate through the for loop
        }
    }

        time += remainingBT[posMinBT];
        remainingBT[posMinBT]=0; //finish the process
        waitingTime[posMinBT] = time - arrivalTime[posMinBT]-burstTime[posMinBT];
        minimumBT = INT_MAX;



if (flag==false)
    break;
}
}
