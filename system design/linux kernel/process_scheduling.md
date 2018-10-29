# Process Scheduling


## What 's process scheduler?

A sub system of kernel that puts processes to work. It decides which process runs, when and for how long.  
The scheduler divides the resource of processor time between the runnable processes on a system

If there are more runnable processes than processors, some processes will not be running at a given moment. These processes are waiting to run

## What's multitasking?
A multitasking OS is one that can simultaneously interleave execution of more than one process.  
Linux can have many processes in memory but only one in a runnable state

## What's preemptive multitasking?

Linux implements preemptive multitasking.  
In preemptive multitasking, the scheduler decides when a process is to cease running and a new process is to begin running.

## What's preemption?
The action of involuntarily suspending a running process is called preemption

## What's timeslice?
The time a process runs before it's preempted is usually predetermined and it's called timeslice of the process

## What's the benefits of preemptive multitasking?
Managing the timeslice enables the scheduler to make global scheduling decisions for the system. It also prevents any  one process from monopolizing the processor.

## What's cooperative multitasking?
A process does not stop running until voluntary decides to do so.

## What's yielding?
The act of a process voluntarily suspending itself is called yielding

## What's the bad thing of it?
Cannot make global decision  
A process never yields can burn down the system

## What's the scheduler in kernel 2.6?
CFS Completely Fair Scheduler

## What's Policy?
Policy is the behavior of the scheduler that determines what runs when.  
The scheduling policy must attempt to satisfy two goals:   
- fast process response time(low latency)
- Maximal system utilization (high throughput)

## What's I/O-Bound process?
Runnable for only short duration because it eventually blocks waiting on more I/O (keyboard input, network I/O or disk I/O)

## What's process-Bound process?
Run less frequently but for longer durations e.g. matlab

## What's process priority?

Linux implements two priority ranks:  
- Nice value: from -20 to +19. Larger nice values correspond to a lower priority- you are being nice to the other processes. Process with lower nice value receive a larger proportion of the system processor. In linux it's a control of the timeslice proportion

- Real-time priority: 0-99 larger value has high priority. All real-time processes are at a higher priority compared with normal processes

## How does timeslice work?

The timeslice is the numeric value that represents how long a task can run until it is preempted.  
Linux CFS  scheduler assigns process a proportion of the processor. The proportion is affected by the nice value

In Linux the preemption decision is a function of how much a proportion of the processor the newly runnable process has consumed. If it has consumed a smaller proportion of the processor than the currently executing process, it runs immediately, preempting the current process. If not , it is scheduled to run at a later time

## What's Scheduler Classes?

Linux scheduler use scheduler classes to enable different algorithms to scheduler different types of processes.

Scheduler classes have priority. The base scheduler class has the highest priority. The highest schedule class that has a runnable process wins and select the next process

Linux CFS is a scheduler class for normal processes

## What's the Cons of the traditional Unix scheduler?
1. Context switching
2. The nice value is a relative term and the difference between 0,1 and 18, 19 is quite large
3. The absolute mapping between timeslice and nice value can cause issues
4. ….

## What's Perfect multitasking?
If we have 2 processes, we would run both processes simultaneously for the same time, each at 50% power.

## How's the Fair scheduling works?

CFS calculates how long a process should run as a function of the total runnable processes.  
The nice value works as a weight regarding the proportion of the processor.  
Each process runs for a "timeslice" proportional to its weight divided by the total weight of all runnable threads.

CFS set a minimum duration called targeted latency as a basis.   
Targeted latency is defined by the number of processes. Therefore, it's a trade off between better interaction and expensive context switch, worse throughput.

Therefore, if we have infinite processes, the targeted latency will be 0.  
So we set a floor of the targeted latency called minimum granularity:1 millisecond 

CFS is not perfect when we have too many processes but it works good for normal situations


# How we account the time via CFS? 
Linux is using struct sched_entity to save related info  
sched_entity  is in the process descriptor

## What's the virtual runtime?
Actual runtime normalized by the number of runnable processes  
It's the ideal estimated runtime for a process on multi processors system.

It's updated by update_curr() which is invoked periodically by system timer and also whenever a process becomes runnable and unrunnable

Vruntime is an accurate measure of the runtime of a given process

## How's the process selection work?
CFS picks the process with the smallest vruntime to run next.

CFS use a red-black tree to manage the list of runnable processes and find the process with the smallest vruntime.   
rbtree( red-black tree) is a self-balancing binary search tree

The key of the rbtree is the vruntime. So we just need to pick up the leftmost node in the tree.  
In linux we don't need to traverse the tree( O(height of the tree) O(LogN) if the tree has n node and is balanced) to find the leftmost node because the value is cached by rb_leftmost.

If leftmost node is null, there are no runnable processes, then CFS schedules the idle task


## How do we add process to the tree?
The process will be added when becominng runnable or firstly created by fork()

Implemented by enqueue_entity()

When do we remove process from the tree?  
CFS removes processes from the tree when the process blocks or terminates

Now What's the workflow of the scheduler?

The main entry point is the function scheduler() which call pick_next_task()  
This function will go through each scheduler class, starting with the highest priority and select the highest priority process in the highest priority class

CFS is a scheduler class for normal processes.


## Where do we store unrunnable processes?
Wait queue: a simple list of processes waiting for an event to occur  
Be careful of the implementation because it can lead to race conditions or dead lock



## What's the context switching?
The switch from one runnable task to another is handled by context_switch()  
This function is called by schedule()  
It does 2 things:  
- Call switch_mm() to switch the virtual memory mapping from the previous process to the new process
- Call switch_to() to switch the process state from the previous state to current process's state

Kernel use a flag to decide when to enable conext switch. Usually it happens when preemption or wake up

The flag is in the thread _info

## Linux kernel is SMP-safe. What's SMP-safe?

SMP is an acronym for Symmetric Multi Processing (meaning multiple CPUs of the same kind - pretty much.)  
It means thread safe.  
Here it means that it's safe for multiple processors to avoid race condition from hardware level.

## How's the kernel process preemption happens?
Thread_info holds a preempt_count  
If preempt_count is>0 , it means other processor is using it therefore it's locked  
If it's 0, it's safe to preempt this process and reschedule


## What's the real-time scheduling policies?
Linux has 2 real-time policies:
- SCHED_FIFO
- SCHED_RR

Those policies 're handled by a special real-time scheduler (schedule class same as CFS)

## What's the detail of SCHED_FIFO?
It's a simple first in first out algorithm without timeslice
1. A runnable SCHED_FIFO task is always scheduled over any normal tasks.
2. When it runnable, it continues to run until it blocks or yields the processor
3. Same priority tasks will run round-robin
4. No timeslice and can run indefinitely.
5. Only a higher priority SCHED_FIFO and SCHED_RR can preempt it

## What's the detail of SCHED_RR? 
Similar to SCHED_FIFO except it has timeslice  
Real-time round-robin algorithm
