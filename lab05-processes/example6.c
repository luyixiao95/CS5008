// |===================================|
// |             Lesson                |
// |===================================|
// This example demonstrates how to have two processes
// 'talk' to each other.
//
// The goal of the end of this lesson is to understand how
// to pipe the output of a child process through the parent.
// (So it will look something like this: child | parent)
// 
// After understanding the fundamentals here however, you should
// be able to pipe input/output between any process you like.
//
// |===================================|
// |  INTERPROCESS COMMUNICATION (IPC) |
// |===================================|
//
// The dirty secret in Unix is that everything is a file.
// Or rather than secret, it is just a useful abstraction!
// This allows us to write very simple programs that do one thing
// very well, and then send the result of that program through another.
// 
// FILE DESCRIPTORS
//
// A file descriptor (usually abbreviated 'fd') is a 
// non-negative integer number. A file descriptor is a 'handle'
// or index used to a file to perform various input/output
// commands.
//
// Each Unix has some default file descriptors for which we
// can stream in and out data.
//
// |-----------------------------------------------------------------|
// |Int Value | Name           | symbolic constant | file stream     |
// |-----------------------------------------------------------------|
// |    0     | Standard Input | STDIN_FILENO      | stdin           |
// |    1     | Standard Output| STDOUT_FILENO     | stdout          |
// |    2     | Standard Error | STDERR_FILENO     | stderr          |
// |-----------------------------------------------------------------|
//
// We can add more file descriptors to this table however. In fact
// when we open a new file (using 'open' or 'fopen') we are creating
// a new handle to some resource (i.e. a file) that we may want to
// read or write new data to.
//
// Okay, so with this knowledge, file descriptors are our 'window'
// or 'channel' for which two processes could potentially talk to each
// other or share data. We just have to know how to connect them together.
//
// In this example, I will show how to make two processes talk to each
// other.
//
// The commands you will learn are
// 
// - fork()
// - waitpid(childpid, status, options)
//      - man waitpid
// - pipe(int pipefd[2])
//      - man 2 pipe
//      - man 7 pipe
// - dup2(int oldfd, int newfd)
//      - man dup
// - close(fd);



// Start of our Program
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(){
    // First, lets see the actual file descriptors and their values.
    // It can be helpful to access them by name instead of memorizing
    // the values 0,1,2.
    //
    // Lets confirm the values of the default file descriptors of our
    // input, output, and error.
    printf("STDIN_FILENO = %d\n", STDIN_FILENO);
    printf("STDOUT_FILENO = %d\n", STDOUT_FILENO);
    printf("STDERR_FILENO = %d\n\n", STDERR_FILENO);

    // Now our goal is to create two processes that can communicate
    // between each other. In order to do this, we will create a 'pipe'
    // between them. We can literally think of this as a 'pipe' connecting
    // together, and creating a channel where information can be passed.
    //
    // -----------|                                      |----------|
    // | Here is  |                                      | Another  |
    // |    a    -|--->------>----->------->------>----->| Process  |
    // | process  | Here is a pipe connecting 2 processes| being    |
    // |         -|-->------->----->------->------>----->| connected|
    // |----------|                                      |----------|
    //              (Notice the flow of information 
    //               from left to right in the pipe)
    //
    // The direction need not always be unidirectional (i.e. a one way channel)
    // But that is what I am going to demonstrate.
    //
    // First, lets have some storage for file descriptors for which
    // our pipes 'read' end and 'write' end will be.
    // Thus, we need an array of two integers to hold our file descriptors.
    int fd[2];
    
    // Now we will use the pipe command that creates two file descriptors for
    // which we can pass information along.
    // (pipe2 also exists if we need more control, but for now let's use pipe).
    // fd[0] is the 'read' end
    // fd[1] is the 'write' end.
    pipe(fd);

    // When I run the above pipe command, two new file descriptors are created
    // as the next available integers. I now have handles to the read
    // and write end of the pipe.
    
    // Let's go ahead and print the file descriptors out to confirm.
    // You should just see two integer values that are different if
    // everything worked correctly. You will also notice that they are
    // not a value of 0,1, or 2, because those are already taken.
    printf("pipe fd[0](for reading) = %d\n", fd[0]);
    printf("pipe fd[1](for writing) = %d\n\n", fd[1]);

    // Now our goal is to do something more interesting and have two
    // separate processes talk to each other.
    // So that means we need to launch another process so we can 
    // connect our pipe between the two processes.
    //
    // Our mechanism to do so is the 'fork()' command. Lets go ahead
    // and fork() to create a new child process. To do this:
   
    // store the child process id somewhere. 
    pid_t childProcessID;
    // store the status somewhere which will tell us when the child
    // process has completed executing. 
    int child_status;

    // execute our fork() and duplicate our parent.
    childProcessID = fork();
    // check that a child was successfully created.
    if(-1 == childProcessID){
        printf("fork failed for some reason!");
        exit(EXIT_FAILURE);
    }

    // Now we want to execute the child code first.
    // Whatever happens in the child, we will output that into our
    // pipe and then our parent will print out the resulting output. 
    // Our pipe can hold quite a bit of 'bytes' of information
    // as the result of whatever our child outputs -- for now we 
    // will do a small example. 
    //
    // Okay, so at this point, lets execute a separate child and parent.
    // Remember, the pid that is returned is '0', then
    // we are in the child process.
    if(childProcessID == 0){
        // Child will execute here -- and it will do so first because
        // we have some synchronization (i.e. a wait) in our parent.
        //
        // Now remember, our child inherits (almost) everything from the parent.
        // This includes the file descriptors.
        // lets print the child file descriptors just to see.
        printf("child copy of pipe fd[0] = %d\n", fd[0]);
        printf("child copy of pipe fd[1] = %d\n\n", fd[1]);

        // Let's do something with our child process, such as execute
        // a command like 'echo' that will output a message.
        // In order to do this, we will use the 'exec' command with
        // the provided arguments.
        //
        // NOTE: execvpe is a one of many different exec commands.
        //       execvpe and execle have an 'e' at the end that allow
        //       us to specify additional environment variables
        //       'exec' commands that contain a 'p' search for commands
        //       in the PATH.
        //       You can try on your shell to 'echo $PATH' to see the default
        //       search paths where programs will be found.
        char* myargv[3];
              myargv[0] = "echo";
              myargv[1] = "hello from child from exec\n";
              myargv[2] = NULL;

        // Okay, now we are going to execute this command in
        // our child process. 
        // However, you will notice in our parent code (the else block)
        // that the parent will always wait for the child. So in this
        // sample, we want our child to execute, and then
        // whatever the output is, we are going to
        // pipe that to our parent process.
        // Our parent process will then exec using the
        // childs output as its input data, reading in from the read end
        // of our pipe.
        //
        // Let's setup the communication through our pipe.
        // (1) First thing is-- we don't want our child to output
        //     as soon as it executes to the terminal.
        close(STDOUT_FILENO);
        
        // (2) Okay, now we do want to capture the output somewhere however!
        //     The 'dup2' command duplicates the file descriptor 
        //     fd[1] into STDOUT_FILENO.
        //     Note: Printing out their values would still be unique, but
        //           they are both writing to the same locations.
        dup2(fd[1], STDOUT_FILENO);
        //   ^
        //   So this means we can now 'write' to our pipe either explicitly
        //   through fd[1] or STDOUT.
        //   
        //   Let's go ahead and write some data into our pipe now.
        //   It won't be printed until later on however.
        dprintf(fd[1], "hello msg from child sent and buffered in pipe\n");

        // So when we are done with a file descriptor (just like a file)
        // we always close it (and now you know when we open a file up, it
        // is just opening up a handle to read and/or write to some file using
        // a file handle or a file descriptor)
        close(fd[1]);   // We are done with fd[1].
        close(fd[0]);   // We also do not need stdin.

        // Now that everything is setup, we can execute our child.
        // We will then use the output from this command, as the input
        // into our parent.
        execvp(myargv[0], myargv);
    } else {
        // Our Parent process will execute this section of code.
        // In our initial goal, remember we want the child to execute first
        // and then the parent will use the childs output as its input.
        //
        // We specifically want to wait on the child that we created
        // for it to complete its work.
        // The 'waitpid' command allows us to wait on a specific child process
        // id. And we have this childProcessID stored, so we use that.
        waitpid(childProcessID, &child_status, NULL);
       
        // Okay, now lets finish off process communication.

        close(STDIN_FILENO); // close stdin, because that is going to come
                             // from our child process.
        dup2(fd[0], 0);      // Our 'new' stdin is going to come from the
                             // read end of the pipe.
        close(fd[1]);        // We can also close the 'write' file desc.
                             // because from our parent we can simply
                             // write out to STDOUT_FILENO by default.

        // Now we can write out the data that is in our pipe.
        // The data has been sitting in a buffer in our pipe, and is
        // ready to be 'flushed' out and written through STDOUT.
        // We are going to do this one character at a time. 
        printf("======= In parent process =====\n");
        char c;
        while(read(STDIN_FILENO, &c, 1) > 0){
            write(STDOUT_FILENO, &c, 1);
        }
        // And at this point, we are done!
    } 


    return 0;
}
