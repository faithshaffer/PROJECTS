//
//  main.c
//  DiscreteEventSimulation
//
//  Created by Faith Shaffer
//
// Compile/Run Instructions: Zeus -> gcc -std=c99 -x c main.c -lm -> ./a.out 12 0.02 0.06
//
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>


//---EVENT LIST---
#define arrival 1
#define proc_toRQ 2
#define proc_toCPU 3
#define departure 4
#define proc_toDQ 5
#define proc_toDISK 6


//---EVENT STRUCT---
struct event{
    float time;
    int type;
    int process_id;
    struct event* next;
   
};

//---PROCESS STRUCT---
struct process{
    int id;
    float arrival_time;
    float CPU_service_time;
    float disk_service_time;
    float remaining_time;
    float start_time;
    float completion_time;
    struct event* next;
};

//--READY QUEUE STRUCT---
struct ready_queue{
    struct process* rq_process;
    struct ready_queue* next;
};

//--DISK QUEUE STRUCT---
struct disk_queue{
    struct process* dq_process;
    struct disk_queue* next;
};

//---FUNCTION PROTOTYPES---
void handle_proc_toCPU(void);
void handle_proc_toRQ(void);
void handle_proc_toDISK(void);
void handle_proc_toDQ(void);
void handle_arrival(float);
void init_( int avg_arrival_rate, float avg_diskservice_time, float avg_CPUservice_time);
int run_simulation(void);
void proc_metrics_report(void);
int next_arrival(struct event* new_event);
float gen_exp(float lambda);
struct process* generate_process(float lambda, float CPU_mu,float disk_mu, int process_id);
void insert_ready_queue(struct process* rq_process);
void remove_ready_queue(struct process* rq_process);
void remove_disk_queue(struct process* dq_process);
void insert_disk_queue(struct disk_queue* dq_process);
struct process* get_next_process(void);

//---GLOBAL VARIABLES---
struct event* event_queue_head;         // head of event queue
struct disk_queue* disk_queue_head;     // head of disk queue
struct ready_queue* ready_queue_head;   // head of ready queue

float current_time; // simulation clock
float lambda; // average arrival rate (in processes/second)
float CPU_mu; // avg CPU service time (in seconds)
float disk_mu; // avg disk service time
int diskq_count = 0;
int readyq_count = 0;
bool disk_idle = 1;
bool cpu_idle = 1;
int exit_count =0; //# of processes completed

struct process* generate_process(float lambda, float CPU_mu,float disk_mu, int process_id) {
    struct process* p = malloc(sizeof(struct process));
    p->id = process_id;
    p->arrival_time = current_time;
    p->CPU_service_time = gen_exp(CPU_mu);
    p->disk_service_time = gen_exp(disk_mu);
    p->remaining_time = p->CPU_service_time + p->disk_service_time;  // set the initial value of remaining_time
    p->next = NULL;
    return p;
}

void init(int argc, char* argv[]) {
    if (argc < 4) {
           printf("Usage: %s <lambda> <avg_CPUservice_time> <avg_diskservice_time>\n", argv[0]);
           exit(1);
       }

    lambda = atof(argv[1]);
    CPU_mu = atof(argv[2]);
    disk_mu = atof(argv[3]);
    
    // seed random number
    srand((unsigned) time(NULL));
    
    current_time = 0;
    exit_count = 0;
    
    event_queue_head = NULL;
    ready_queue_head = NULL;
    disk_queue_head = NULL;
}

void init_(int avg_arrival_rate, float avg_CPUservice_time, float avg_diskservice_time) {
    //event_queue_head = ;
    current_time = 0.0;
    
    lambda = avg_arrival_rate;
    disk_mu = 1.0 / avg_diskservice_time;
    CPU_mu = 1.0 / avg_CPUservice_time;
    
    // schedule first event
    struct event* first_arrival_event = (struct event*) malloc(sizeof(struct event));
    first_arrival_event->time = 0;
    first_arrival_event->type = arrival;
    first_arrival_event->process_id = 0;
    next_arrival(first_arrival_event);
    
}

//---GENERATES RANDOM SERVICE & ARRIVAL TIMES---
float gen_exp(float lambda) {
  srand((unsigned) time(NULL));
  float u,x;
  x = 0;
  while (x == 0) {
    u = rand();
    x = ((-1/lambda)*log(u));
  }
  return(x);
}

//-----HANDLE PROCESS ARRIVAL-----
void handle_arrival(float arrival_time) {
    //schedule_event(new_event);
    // create new process
    struct process* p = malloc(sizeof(struct process));
    p->arrival_time = arrival_time;
    p->CPU_service_time = gen_exp(CPU_mu);
    p->disk_service_time = gen_exp(disk_mu);
    p->next = NULL;
    
    current_time++;
    if (cpu_idle == 1) {
        cpu_idle = 0; //setting cpu to busy
        handle_proc_toCPU();
 } else {
     handle_proc_toRQ();
}
 }

//-----HANDLE PROCESS TO DISK-----
void handle_proc_toDISK() {
    diskq_count--;
    current_time++;
    exit_count++;
    //removing process from DQ
    struct disk_queue* event;
    event = disk_queue_head;
    //disk_queue_head = event->next;
    free(event);
    event = NULL;
    
    disk_idle = 1;
    handle_arrival(current_time);
 }
 
//-----HANDLE PROCESS TO DISK QUEUE-----
void handle_proc_toDQ() {
     if (disk_idle == 1) {
        disk_idle = 0;
        handle_proc_toDISK();
         
 } else {
    diskq_count++;
     //insert process to end of DQ
     struct disk_queue* p;
     p = malloc(sizeof(struct disk_queue));
     p -> next = NULL;
     struct disk_queue* temp = disk_queue_head;
     while (temp -> next != NULL) {
         temp = temp-> next;
     } temp -> next = p;
 }
 }

//-----HANDLE PROCESS DEPARTURE-----
int handle_departure(float completion_time, int exit_count) {
    exit_count++;
    current_time++;   //update and record current time
    current_time = completion_time;
    // get turnaround time for process
   
    return (exit_count++);
 }

//-----HANDLE PROCESS TO CPU-----
void handle_proc_toCPU() {
    readyq_count--;
    current_time++;
    
    //removing process from RQ
    struct ready_queue* event;
    event = ready_queue_head;
//    ready_queue_head = event->next;
    free(event);
    event = NULL;
    
    //--COIN FLIP TO EXIT OR GO TO DISK QUEUE---
    srand((unsigned) time(NULL));
    for (int count = 0; count <= 15000; ++count) {
        float random = (double)rand() / RAND_MAX;
        if (random <= 0.6){
            handle_departure(current_time, exit_count);
        } else {
            handle_proc_toDQ();
        }
    }
    cpu_idle = 1;
}
 
 //-----HANDLE PROCESS TO READY QUEUE-----
void handle_proc_toRQ() {
    readyq_count++;
    if (cpu_idle == 1) {
        cpu_idle = 0; //setting cpu to busy
        handle_proc_toCPU();
    } else {
        //insert_ready_queue(struct process* rq_process);
        struct ready_queue* p;
        p = malloc(sizeof(struct ready_queue));
        p -> next = NULL;
        //struct ready_queue* temp = ready_queue_head;
        //while (temp -> next != NULL) {
          //  temp = temp-> next;
        }// temp -> next = p;
    }
//}
 
//-----RUN SIMULATION-----
int run_simulation() {
       struct event* this_event;
        
    while (exit_count < 10000)
    {
        this_event = event_queue_head;
        
        current_time++;
    
        //switch (this_event->type)
        //{
           // case arrival:
                handle_arrival(current_time);
               /* break;
            //case proc_toRQ:
                handle_proc_toRQ();
                break;
            case proc_toCPU:
                handle_proc_toCPU();
                break;
            case departure:
                handle_departure(current_time);
                break;
            case proc_toDQ:
                handle_proc_toDQ();
                break;
            case proc_toDISK:
                handle_proc_toDISK();
                break;
            default:
                printf("Error: invalid event type\n");
                exit(1);*/
//}
    //schedule_event(struct event *new_event);
        //removes event from event queue
    //event_queue_head = this_event;
       // free(this_event);
        //this_event = NULL;
    }
    return 0;
}

//-----GENERATE PROCESS METRICS REPORT-----
void proc_metrics_report() {
    float completion_time = 0;
    float arrival_time = 0;
    float avg_turnaround_time;
    float turnaround_time;
   // float total_turnaround_time = 0;
    float avg_throughput;
    float avg_cpu_utilization = CPU_mu;
    float avg_disk_utilization = disk_mu;
    //int total_processes_completed = exit_count;
    double avg_proc_in_readyq;
    double avg_proc_in_diskq;
   // int total_cpu_busy_time;
   // int total_disk_busy_time;
    
    //---PROCESS METRICS COMPUTATIONS---
    turnaround_time = completion_time - arrival_time;
    //total_turnaround_time =   //sum of all turnaround times collected
    avg_turnaround_time = turnaround_time / exit_count;
    avg_throughput = exit_count / current_time;
    avg_proc_in_readyq =  readyq_count ;
    avg_proc_in_diskq = diskq_count / exit_count;
    
    //---OUTPUTS PROCESS METRICS STATISTICS---
    printf("Average Turnaround Time: %f\n", avg_turnaround_time);
    printf("Average Throughput: %f\n", avg_throughput);
    printf("Average CPU Utilization: %f\n", avg_cpu_utilization);
    printf("Average Disk Utilization: %f\n", avg_disk_utilization);
    printf("Average Number of Processes in the CPU Ready Queue: %f\n", avg_proc_in_readyq);
    printf("Average Number of Processes in the Disk Queue: %f\n", avg_proc_in_diskq);
    printf("EXIT #: %f\n", exit_count);
}

//-----MAIN FUNCTION-----
int main(int argc, char *argv[] ) {
  // command-line arguments
  if (argc < 3) {
    printf("[avg_arrival_rate] [avg_CPUservice_time] [avg_diskservice_time]\n");
      return 0;
  }
  
  int avg_arrival_rate = atoi(argv[1]);
  float avg_CPUservice_time = atof(argv[2]);
  float avg_diskservice_time = atof(argv[3]);


  init_(avg_arrival_rate, avg_diskservice_time, avg_CPUservice_time);
  run_simulation();
  proc_metrics_report();

  return 0;
}

//-----SCHEDULES NEXT ARRIVAL-----
int next_arrival(struct event* new_event) {
  struct event* current_event;
  if (event_queue_head == NULL || new_event->time < event_queue_head->time) {
    // insert at beginning
    new_event->next = event_queue_head;
    event_queue_head = new_event;
  } else {
    current_event = event_queue_head;
    while (current_event->next != NULL && new_event->time > current_event->next->time) {
      current_event = current_event->next;
    }
    new_event->next = current_event->next;
    current_event->next = new_event;
  }
  return 0;
}


