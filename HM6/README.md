# Thread

In this week, we learned about thread mostly. In this README file, I am going to introduce you some basic concepts about threads and the functions inside.


## 1.Introduction of Thread
### What is a thread
Technically, a thread is defined as an independent stream of instructions that can be scheduled to run as such by the operating system.
To the software developer, the concept of a “procedure” that runs independently from its main program may best describe a thread.

To go one step further, imagine a main program (a.out) that contains a number of procedures. Then imagine all of these procedures being able to be scheduled to run simultaneously and/or independently by the operating system. That would describe a “multi-threaded” program.
### What is a p_thread
Historically, hardware vendors have implemented their own proprietary versions of threads. These implementations differed substantially from each other making it difficult for programmers to develop portable threaded applications.

In order to take full advantage of the capabilities provided by threads, a standardized programming interface was required.

For UNIX systems, this interface has been specified by the IEEE POSIX 1003.1c standard (1995).
Implementations adhering to this standard are referred to as POSIX threads, or Pthreads.
Most hardware vendors now offer Pthreads in addition to their proprietary API’s.

## p_thread APIs

The subroutines which comprise the Pthreads API can be informally grouped into four major groups:

**Thread management**: Routines that work directly on threads - creating, detaching, joining, etc. They also include functions to set/query thread attributes (joinable, scheduling etc.)

**Mutexes**: Routines that deal with synchronization, called a “mutex”, which is an abbreviation for “mutual exclusion”. Mutex functions provide for creating, destroying, locking and unlocking mutexes. These are supplemented by mutex attribute functions that set or modify attributes associated with mutexes.

**Condition variables**: Routines that address communications between threads that share a mutex. Based upon programmer specified conditions. This group includes functions to create, destroy, wait and signal based upon specified variable values. Functions to set/query condition variable attributes are also included.

**Synchronization**: Routines that manage read/write locks and barriers.

## Introdcution of some most important p_thread functions

### pthread_t

pthread_t is the data type used to uniquely identify a thread. It is returned by pthread_create() and used by the application in function calls that require a thread identifier. The thread is created running start_routine, with arg as the only argument.

### pthread_create

The pthread_create() function is used to create a new thread, with attributes specified by attr, within a process. If attr is NULL, the default attributes are used. If the attributes specified by attr are modified later, the thread's attributes are not affected. Upon successful completion, pthread_create() stores the ID of the created thread in the location referenced by thread.

### pthread_join

The pthread_join() function shall suspend execution of the calling thread until the target thread terminates, unless the target thread has already terminated. On return from a successful pthread_join() call with a non-NULL value_ptr argument, the value passed to pthread_exit() by the terminating thread shall be made available in the location referenced by value_ptr. When a pthread_join() returns successfully, the target thread has been terminated. The results of multiple simultaneous calls to pthread_join() specifying the same target thread are undefined. If the thread calling pthread_join() is canceled, then the target thread shall not be detached.

It is unspecified whether a thread that has exited but remains unjoined counts against {PTHREAD_THREADS_MAX}.

The behavior is undefined if the value specified by the thread argument to pthread_join() does not refer to a joinable thread.

The behavior is undefined if the value specified by the thread argument to pthread_join() refers to the calling thread.

### pthread_exit

The pthread_exit() function terminates the calling thread and makes the value value_ptr available to any successful join with the terminating thread. Any cancellation cleanup handlers that have been pushed and not yet popped are popped in the reverse order that they were pushed and then executed. After all cancellation cleanup handlers have been executed, if the thread has any thread-specific data, appropriate destructor functions will be called in an unspecified order. Thread termination does not release any application visible process resources, including, but not limited to, mutexes and file descriptors, nor does it perform any process level cleanup actions, including, but not limited to, calling any atexit() routines that may exist.
An implicit call to pthread_exit() is made when a thread other than the thread in which main() was first invoked returns from the start routine that was used to create it. The function's return value serves as the thread's exit status.

The behaviour of pthread_exit() is undefined if called from a cancellation cleanup handler or destructor function that was invoked as a result of either an implicit or explicit call to pthread_exit().

After a thread has terminated, the result of access to local (auto) variables of the thread is undefined. Thus, references to local variables of the exiting thread should not be used for the pthread_exit() value_ptr parameter value.

The process exits with an exit status of 0 after the last thread has been terminated. The behaviour is as if the implementation called exit() with a zero argument at thread termination time.


## Reference
https://hpc-tutorials.llnl.gov/posix/
https://www.ibm.com/docs/en/zos/2.4.0?topic=functions-pthread-create-create-thread
https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_join.html
https://pubs.opengroup.org/onlinepubs/007908799/xsh/pthread_exit.html
