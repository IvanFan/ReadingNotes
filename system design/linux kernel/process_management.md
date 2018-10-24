## Process Management

This is a reading notes regarding the Linux Kernel Development


### What is process and what is thread?
Process: is a program in the midst of execution, also include a set of resources


Thread: the objects of activity within the process. Includes: a unique program counter, process stack, Set of process registers 


The kernel schedules threads not process.


To linux, a thread is implemented as a special kind of process


Process provides two virtualizations  
- Virtualized processor (schedule): it gives the process the illusion that it alone monopolizes the system.
- Virtual memory (memory): let the process allocate the manage memory as if it alone owned all the memory in the system.


Threads share the virtual memory abstraction whereas each receives its own virtualized processor


Process is an active program
Two and more processes can exist that are executing the same program, sharing various resources



### How the process begins?

The existing process will create another process by calling fork()  
The existing process is parent  
The new process is child   
The parent process will resume execution and the child process will start the execution both when the fork() return


The fork() system call return twice from kernel: one in parent process another one in the child process

### What happens after creation?

The process will execute a new, different program. The exec() family of function calls creates new address space and loads a new program into it.


### How does the process end?


A program exits via exit() system call. This call terminates the process and free resources.
The parent process can inquire about the status of a terminated child via wait4() system call, which enables a process to wait for the termination of a specific process. 
When the process exists, it's placed into a special zombie state that represents terminated processes until the parent calls wait() or waitpid()


Another name for a process is a task!


### How does  the kernel store all those processes?
The kernel stores list of processes in a circular doubly linked list called Task List

### What's process descriptor?
Each element in the task list is a process descriptor. Each process descriptor is of the type: struct task_struct which is defined in <linux/sched.h>
The process descriptor contains all the info about a specific process. 


The task_struct contains the data e.g. open files, the process's address space, pending signals, the process's state and etc

### How to allocate the process descriptor

The task_struct is allocated via slab allocator  
   
With the process descriptor dynamically created by slab allocator, a new structure  thread_info will be generated and live at the bottom of the stack (for stack that grows down) or top of the stack (for stack that grows up)

thread_info has a pointer to the  task_struct

Each task's thread_info is allocated a the end of its stack.

### How to get the current working process descriptor?

Each process has a unique id called PID saved in each porcess descriptor

Pid_max defines the max number of pid. A value to estimated concurrency

In the system, we can use current macro to directly use the current process
In x86, current is calculated via masking out  13 least-significant bits of the stack pointer to obtain the thread_info

This calculation is done within current_thread_info() 
To get the current task_struct: current_thread_info()->task

### What's process state?

The state field in the process descriptor present the current condition of the process
There are 5 different states:  
- TASK_RUNNING: the process is runnable. It's either currently running or wait for running in the queue. It's the only state for process executing in user-space. In kernel-space, it presents that the process is actively running
- TASK_INTERRPTIBLE: the process is sleeping(blocked) and wait for some conditions to exists. When it exists, the kernel will set the process to TASK_RUNNING. The process can also be awaken by signals
- TASK_UNINTERPTIBLE: it's the same state of TASK_INTERRPTIBLE except that it will not be awaken by signals
- _TASK_TRACED: the process is been traced by other processes e.g. debugger via ptrace
- _TASK_STOPPED: process is stopped nor is it eligible to run. This occurs if the task receives SIGSTOP, SIGSTP,SIGTTIN or SIGTTOU signal or any signal while it's being debugged

### How to change the process state?

Call set_task_state(task, state)
set_current_state is sync to above function


### What's process context?
For each process it will read the execuable code from the execuable files and execute the code in the progress's address space. Normal program is executed in user-space. If its's called by system call or trigger an exception, then the process enters in the kernel space
 At this point, the kernel is said to be 'executing on behalf of the process' and is in process context

After exiting the kernel, the process resumes execution in user-space


### What's process family tree?
All processes are descendants of the init process, whose pid is one.  
The kernel starts init in the last step of the boot process and init process reads the system initscripts and execute more programs

Each process has one parent but 0-more children. Process that has same parent are siblings.
The relation is saved in process descriptor, with a pointer called parent   
Another list pointers call children.   
It's easy to iterate over all processes in the system because task list is a circular doubly linked list
But expensive time cost


### How to create a process in details?

Two steps in unix: fork() and exec()  
- Fork() create a child process that is a copy of the current task except pid and certain resources and statistics  
PPID is parent's pid
- exec() loads a new execuable into the address space and executes it

Linux implement fork() via clone() system call via do_fork() via copy_process()
1. It calls dup_task_struct() to create new kernel stack, thread_info and task_struct. At this point the child and parent descriptor are the same
2. Check pid is within the max limit
3. Child process differentiate itself from the parent process
4. Call copy_flags() to update flag of task_struct
5. Child state is set to TASK_UNINTERRUPTIBLE to ensure that it doesn't yet run
6. Call alloc_pid() to create a new pid
7. Either duplicate or share resources: open files, filesystem information, signal handlers, process address space and namespace. Those are shared between threads in a process or unique and copied for different process
8. copy_process() cleanup and return the caller a pointer to new process
	

### What's Copy-on-Write? (Known as COW in other system)

Rather than duplicate the process address space, the parent and the child can share a single copy.  
The data is marked that if it is written to , a duplicate is made and each process receives a unique copy. COW delays the copying of each page in the address space until it is actually written to.


### What's kernel threads?

It's useful for kernel to perform some operation in the background.  It's done via kernel threads.  
It's standard process that exist solely in kernel-space.  
Kernel thread doesn't have an address space. They never context switch into user-space

 
### How to terminate a process?

When a process terminates , the kernel release the resources owned by the process and notifies the parent process
The process calls exit() to terminate itself.  
The work is handled by do_exit():  
1. Set the PF_EXITING flag of the task_struct
2. Call del_timer_sync() to remove any kernel timers
3. If BSD accounting is enabled, then release it
4. Call exit_mm() to release mm_struct held by this process. If no other process is holding it
5. Call exit_files() and exit_fs() to decrement the usage count of objects related to file descriptors and filesystem data. If the usage count is 0, then the object will be destoryed (GC)
6. It sets the exit_code in the task_struct
7. Call exit_notify() to send signals to the parent, reparents children process to another thread in their thread group or init process. Then set the exit state in the exit_state in task_struct to EXIT_ZOMBIE	
8. do_exit() call schedule() to switch to a new process

All objects associated with the task are freed. The only memeory it holds is itskernel stack the thread_info and task_Struct. After the parent retrieves the info or notifies the kernel of the received. The remaining memory will be released


