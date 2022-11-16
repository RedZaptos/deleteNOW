#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sched.h>
#include<math.h>
#include<time.h>

pthread_t a;
pthread_t b;
pthread_t c;
int priorityA;
int priorityB;
int priorityC;

long iniA; 
long iniB; 
long iniC; 

long finA; 
long finB; 
long finC;

void print_histogram(double execution_time_A , double execution_time_B , double execution_time_C){
	execution_time_A/=CLOCKS_PER_SEC; 
	execution_time_B/=CLOCKS_PER_SEC; 
	execution_time_C/=CLOCKS_PER_SEC; 

    printf("\nHISTOGRAM \n");
    printf("Standard Linux Scheduling:\n");
    for(int i = 0 ; i<(execution_time_A*20)-100; i++){
        printf("|");
    }
    printf("\n");
    printf("Round Robin Scheduling:\n");
    for(int i = 0 ; i<(execution_time_B*20)-100 ; i++){
        printf("|");
    }
    printf("\n");
    printf("First-In-First-Out Scheduling:\n");
    for(int i = 0 ; i<(execution_time_C*20)-100 ; i++){
        printf("|");
    }
    printf("\n\n");
}


void* countA(void* args){
    iniA = clock(); 
    struct sched_param paramA;
    paramA.sched_priority = priorityA; 
    pthread_setschedparam(a, SCHED_OTHER, &paramA);
    for(long int i = 1 ; i<4294967296 ; i++){
        continue; 
    }
    finA=clock(); 
    return NULL ; 
}

void* countB(void* args){
    iniB = clock(); 
    struct sched_param paramB;
    paramB.sched_priority = priorityB; 
    pthread_setschedparam(b, SCHED_RR, &paramB);
    for(long int i = 1 ; i<4294967296 ; i++){
        continue; 
    }
    finB=clock(); 
    return NULL ; 
}

void* countC(void* args){
    iniC = clock(); 
    struct sched_param paramC;
    paramC.sched_priority = priorityC; 
    pthread_setschedparam(c, SCHED_FIFO, &paramC);
    for(long int i = 1 ; i<4294967296 ; i++){
        continue; 
    }
    finC=clock(); 
    return NULL ; 
}

int main(){
	printf("------------------------------\n");
    printf("For my system: \n");
    printf("OTHER Scheduling policy: %d\n", SCHED_OTHER);
    printf("RR Scheduling policy: %d\n", SCHED_RR);
    printf("FIFO Scheduling policy: %d\n", SCHED_FIFO);
    printf("------------------------------\n");

    pthread_create(&a, NULL, &countA, NULL);
    pthread_create(&b, NULL, &countB, NULL);  
    pthread_create(&c, NULL, &countC, NULL);
    
    pthread_join(a, NULL); 
    pthread_join(b, NULL);
    pthread_join(c, NULL);

    printf("OTHER: %lf\n", (double)(finA-iniA)/CLOCKS_PER_SEC);
    printf("RR: %lf\n", (double)(finB-iniB)/CLOCKS_PER_SEC);
    printf("FIFO: %lf\n", (double)(finC-iniC)/CLOCKS_PER_SEC);

    print_histogram(finA-iniA,finB-iniA ,finC-iniA); 

	return 0; 
}


