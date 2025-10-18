// File:	thread-worker.c
// List all group member's name: Shlok Bohra, Ayush Patel
// username of iLab:
// iLab Server:

#include "thread-worker.h"
#define STACK_SIZE SIGSTKSZ


//Global counter for total context switches and 
//average turn around and response time
long tot_cntx_switches=0;
double avg_turn_time=0;
double avg_resp_time=0;


// INITAILIZE ALL YOUR OTHER VARIABLES HERE
int num_of_threads=0;
double total_turn_time=0;
double total_resp_time=0; 

int currThreadID = 1;

// YOUR CODE HERE



typedef struct{
	int items[100];
    int back;
    int front;
} Queue;

void initializeQueue(Queue* q){
	q->front = -1;
    q->back = 0;
}
bool isEmpty(Queue* q){
	return (q->front == q->back - 1);
}
bool isFull(Queue* q){
	return (q->back == 100);
}
void enqueue(Queue* q, int thread1){
	if (isFull(q)) {
		printf("MAX SIZE reached, can't enqueue\n");
        return;
    }
    q->items[q->back] = thread1;
    q->back++;
}
void dequeue(Queue* q, int thread1){
	if (isEmpty(q)) {
        printf("Nothing to dequeue\n");
        return;
    }
    q->front++;
}
int peek(Queue* q)
{
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return -1; // return some default value or handle
    }
    return q->items[q->front + 1];
}

void dummyFunc(void){}

/* create a new thread */
int worker_create(worker_t * thread, pthread_attr_t * attr, 
                      void *(*function)(void*), void * arg) {

	(void)attr;
		tcb *thrd = (tcb *)malloc(sizeof *thrd);
		thrd->stack = malloc(STACK_SIZE);
		thrd->ThreadID = currThreadId; currThreadId++;
		thrd->priority = 0; //base priority
		thrd->next = NULL;
		thrd->CurrThreadState = READY;

		if (getcontext(&thrd) < 0){
		perror("getcontext");
		free(thrd->stack);
		free(thrd);
		exit(1);
	}


	
		thrd->threadCtx.uc_stack.ss_size = STACK_SIZE;
		thrd->threadCtx.uc_stack.ss_sp = thrd->stack;
		thrd->threadCtx.uc_link = NULL;
		thrd->threadCtx.uc_stack.ss_flags = 0;

		makecontext(&thrd->threadCtx, (void*)&dummyFunc,1, arg);
		thread = thrd->ThreadID;

       // - create Thread Control Block (TCB)
       // - create and initialize the context of this worker thread
       // - allocate space of stack for this thread to run
       // after everything is set, push this thread into run queue and 
       // - make it ready for the execution.

       // YOUR CODE HERE


	
	
    return 0;
};

/* give CPU possession to other user-level worker threads voluntarily */
int worker_yield() {
	
	// - change worker thread's state from Running to Ready
	// - save context of this thread to its thread control block
	// - switch from thread context to scheduler context

	// YOUR CODE HERE
	
	return 0;
};

/* terminate a thread */
void worker_exit(void *value_ptr) {
	// - de-allocate any dynamic memory created when starting this thread

	// YOUR CODE HERE
};


/* Wait for thread termination */
int worker_join(worker_t thread, void **value_ptr) {
	
	// - wait for a specific thread to terminate
	// - de-allocate any dynamic memory created by the joining thread
  
	// YOUR CODE HERE
	return 0;
};

/* initialize the mutex lock */
int worker_mutex_init(worker_mutex_t *mutex, 
                          const pthread_mutexattr_t *mutexattr) {
	//- initialize data structures for this mutex

	// YOUR CODE HERE
	return 0;
};

/* aquire the mutex lock */
int worker_mutex_lock(worker_mutex_t *mutex) {

        // - use the built-in test-and-set atomic function to test the mutex
        // - if the mutex is acquired successfully, enter the critical section
        // - if acquiring mutex fails, push current thread into block list and
        // context switch to the scheduler thread

        // YOUR CODE HERE
        return 0;
};

/* release the mutex lock */
int worker_mutex_unlock(worker_mutex_t *mutex) {
	// - release mutex and make it available again. 
	// - put threads in block list to run queue 
	// so that they could compete for mutex later.

	// YOUR CODE HERE
	return 0;
};


/* destroy the mutex */
int worker_mutex_destroy(worker_mutex_t *mutex) {
	// - de-allocate dynamic memory created in worker_mutex_init

	return 0;
};

/* Pre-emptive Shortest Job First (POLICY_PSJF) scheduling algorithm */
static void sched_psjf() {
	// - your own implementation of PSJF
	// (feel free to modify arguments and return types)

	// YOUR CODE HERE
	int time_waiting = 0
    int turnaround_time = 0;
	int response_time = 0; 

	//shortest time quantums into queue, then parse by that. 
	

	//somewhere towards the end, divide all turnaround time and response time by number of threads. 
}


/* Preemptive MLFQ scheduling algorithm */
static void sched_mlfq() {
	// - your own implementation of MLFQ
	// (feel free to modify arguments and return types)

	// YOUR CODE HERE

	/* Step-by-step guidances */
	// Step1: Calculate the time current thread actually ran
	// Step2.1: If current thread uses up its allotment, demote it to the low priority queue (Rule 4)
	// Step2.2: Otherwise, push the thread back to its origin queue
	// Step3: If time period S passes, promote all threads to the topmost queue (Rule 5)
	// Step4: Apply RR on the topmost queue with entries and run next thread
}

/* Completely fair scheduling algorithm */
static void sched_cfs(){
	// - your own implementation of CFS
	// (feel free to modify arguments and return types)

	// YOUR CODE HERE

	/* Step-by-step guidances */

	// Step1: Update current thread's vruntime by adding the time it actually ran
	// Step2: Insert current thread into the runqueue (min heap)
	// Step3: Pop the runqueue to get the thread with a minimum vruntime
	// Step4: Calculate time slice based on target_latency (TARGET_LATENCY), number of threads within the runqueue
	// Step5: If the ideal time slice is smaller than minimum_granularity (MIN_SCHED_GRN), use MIN_SCHED_GRN instead
	// Step5: Setup next time interrupt based on the time slice
	// Step6: Run the selected thread
}


/* scheduler */
static void schedule() {
	// - every time a timer interrupt occurs, your worker thread library 
	// should be contexted switched from a thread context to this 
	// schedule() function
	
	//YOUR CODE HERE

	// - invoke scheduling algorithms according to the policy (PSJF or MLFQ or CFS)
// #if defined(PSJF)
//     	sched_psjf();
// #elif defined(MLFQ)
// 	sched_mlfq();
// #elif defined(CFS)
//     	sched_cfs();  
// #else
// 	# error "Define one of PSJF, MLFQ, or CFS when compiling. e.g. make SCHED=MLFQ"
// #endif
}



//DO NOT MODIFY THIS FUNCTION
/* Function to print global statistics. Do not modify this function.*/
void print_app_stats(void) {

       fprintf(stderr, "Total context switches %ld \n", tot_cntx_switches);
       fprintf(stderr, "Average turnaround time %lf \n", avg_turn_time);
       fprintf(stderr, "Average response time  %lf \n", avg_resp_time);
}


// Feel free to add any other functions you need

// YOUR CODE HERE



